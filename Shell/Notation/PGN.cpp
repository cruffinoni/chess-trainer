
#include <sstream>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <optional>
#include "PGN.hpp"
#include "FEN.hpp"

bool ChessTrainer::Notation::PGN::updateCursor(const std::string& input,
                                               const int currentMove,
                                               size_t& startIdx,
                                               std::string& buffer) {
    const auto& moveFound = input.find(std::to_string(currentMove + 1) + ".");
    if (moveFound == std::string::npos) {
        const static std::vector<std::string> validGameState = {
            {"1/2-1/2"},
            {"1-0"},
            {"0-1"},
            {"*"},
        };
        for (const auto& vgs: validGameState) {
            const auto& endgame = input.find(vgs);
            if (endgame == std::string::npos)
                continue;
            buffer = input.substr(startIdx, endgame - (startIdx + 1));
            startIdx = endgame;
            return false;
        }
        return false;
    }
    buffer = input.substr(startIdx, moveFound - (startIdx + 1));
    startIdx = moveFound;
    return true;
}

void ChessTrainer::Notation::PGN::getGameState(
    const std::string& input) {
    const static std::vector<std::pair<std::string, Board::gameState_t>>
        validGameState = {
        {"1/2-1/2", Board::ENDED | Board::DRAW},
        {"1-0",     Board::ENDED | Board::WHITE},
        {"0-1",     Board::ENDED | Board::BLACK},
        {"*",       Board::IN_PROGRESS},
    };
    for (const auto& s: validGameState) {
        const auto& m = input.find(s.first);
        if (m != std::string::npos) {
            //if (m + s.first.size() != input.size()) // TODO: Add this but remove blank lines/spaces
            //    throw Error(Error::GAME_RESULT_INVALID_PLACEMENT);
            this->board_.setGameState(s.second);
            //std::cout << "Last move detected ; state of the game -> "
            //          << this->board_.getGameStateName() << std::endl;
            return;
        }
    }
    throw Error(Error::GAME_RESULT_MISSING);
}

void ChessTrainer::Notation::PGN::removeComments(std::string& buffer) {
    size_t
        countCommentOpenToken = std::count(buffer.begin(), buffer.end(), '{');
    size_t
        countCommentCloseToken = std::count(buffer.begin(), buffer.end(), '}');
    if (countCommentOpenToken > countCommentCloseToken)
        throw Error(Error::COMMENTARY_MISSING_END_TOKEN);
    else if (countCommentOpenToken < countCommentCloseToken)
        throw Error(Error::COMMENTARY_MISSING_OPEN_TOKEN);
    else if (countCommentCloseToken > 1 || countCommentCloseToken > 1)
        throw Error(Error::NESTED_COMMENTARY, buffer);
    size_t commentaryOpenToken;
    while ((commentaryOpenToken = buffer.find_first_of('{'))
        != std::string::npos) {
        size_t commentaryCloseToken = buffer.find_first_of('}');
        if (commentaryCloseToken == std::string::npos)
            throw Error(Error::COMMENTARY_MISSING_END_TOKEN);

        // TODO: Stocker le commentaire
        buffer.erase(commentaryOpenToken,
                     commentaryCloseToken - commentaryOpenToken + 1);
    }
}

void ChessTrainer::Notation::PGN::removeRecurrentMoveNumber(std::string& buffer,
                                                            int move) {
    const auto
        removePart = [&buffer](const std::string& toRemove) -> void {
        size_t start = buffer.find(toRemove);
        if (start != std::string::npos)
            buffer.erase(start, toRemove.length());
    };
    removePart(std::to_string(move) + ".");
    removePart(std::to_string(move) + "...");
}

void ChessTrainer::Notation::PGN::removeCheckOrMate(std::string& buffer) {
    const auto& pieceIdx = buffer.find_first_of("+#");
    this->board_.removeGameState(Board::IN_CHECK | Board::IN_CHECKMATE);
    if (pieceIdx == std::string::npos)
        return;
    if (buffer[pieceIdx] == '+') {
        this->board_.addGameState(Board::IN_CHECK);
        //printf("[c/m] in check\n");
    } else {
        this->board_.addGameState(Board::IN_CHECKMATE);
        //printf("[c/m] checkmate\n");
    }
    buffer.erase(pieceIdx, 1);
}

ChessTrainer::IPiece::helperPieceData
ChessTrainer::Notation::PGN::getPieceDataFromNotation(
    const std::string& originalMove,
    const std::string& notation,
    const IPiece::Color& color) {
    IPiece::helperPieceData p {
        .piece = nullptr,
        .coordinates = Coordinates(notation.substr(notation.length() - 2)),
        .priorLine = -1
    };
    const auto& pieceIdx = notation.find_first_of("RQNKB");
    // Pawn movement
    if (pieceIdx == std::string::npos) {
        if (notation.length() != 2) // Taking a piece
            p.priorLine = notation[0];
        p.piece = std::make_shared<Pawn>(color);
        return p;
    }
    p.piece = createPieceFromDiminutive(color, notation[0]);
    if (p.piece == nullptr)
        throw Error(Error::UNKNOWN_PIECE, originalMove);
    if (notation.length() == 3) // No precision added (eg: Raa3, Rhe6, etc...)
        return p;
    p.priorLine = notation[1];
    return p;
}


std::optional<ChessTrainer::IPiece::helperPieceData>
ChessTrainer::Notation::PGN::checkForTakeMove(
    const std::string& originalMove,
    std::string& move,
    const ChessTrainer::IPiece::Color& color) {
    const auto& takeIdx = move.find_first_of('x');
    // Bxb5
    if (takeIdx == std::string::npos)
        return std::nullopt;
    move.erase(takeIdx, 1);
    return getPieceDataFromNotation(originalMove, move, color);
}

ChessTrainer::IPiece::helperPieceData
ChessTrainer::Notation::PGN::getPiece(std::string move,
                                      const IPiece::Color& color) {
    const std::string& cpy = move.substr();
    const auto& takingPiece =
        ChessTrainer::Notation::PGN::checkForTakeMove(cpy,
                                                      move,
                                                      color);
    if (takingPiece.has_value()) {
        return takingPiece.value();
    }
    return getPieceDataFromNotation(cpy, move, color);
}

ChessTrainer::Board::gameState_t ChessTrainer::Notation::PGN::getCastleType(
    const std::string& buffer,
    const IPiece::Color& color) {
    if (buffer == "O-O")
        return Board::KINGSIDE_CASTLE;
    else if (buffer == "O-O-O")
        return Board::QUEENSIDE_CASTLE;
    else
        return Board::NONE;
}


void ChessTrainer::Notation::PGN::tryToApplyMoveToBoard(const std::string& move,
                                                        ChessTrainer::IPiece::Color color) {
    const auto& castleType = getCastleType(move, color);
    if (castleType != Board::NONE) {
        if (!this->board_.doCastle(castleType, color)) {
            std::ostringstream o;
            o << "for " << color << " at " << move;
            throw Error(Error::INVALID_CASTLE, o.str());
        }
        return;
    }
    if (move.find('=') != std::string::npos) {
        this->applyPromotion(move, color);
        return;
    }
    const auto& piece = getPiece(move, color);
    if (!this->board_.movePiece(piece)) {
        throw Error(Error::ILLEGAL_MOVE, move);
    }
}


void ChessTrainer::Notation::PGN::applyMove(const std::string& move,
                                            int currentMove) {
    auto moveCpy = move.substr();
    removeComments(moveCpy);
    this->removeRecurrentMoveNumber(moveCpy, currentMove);
    auto rawCoordinates = Utils::splitStringBySpace(moveCpy);
    for (auto& c: rawCoordinates)
        this->removeCheckOrMate(c);
    if (rawCoordinates.size() > 2)
        throw Error(Error::INVALID_NUMBER_OF_COORDINATES, move);

    this->tryToApplyMoveToBoard(rawCoordinates[0], IPiece::Color::White);
    if (rawCoordinates.size() > 1)
        this->tryToApplyMoveToBoard(rawCoordinates[1], IPiece::Color::Black);
}

void ChessTrainer::Notation::PGN::readMoves(const std::string& input) {
    int currentTotalMove = 1;
    size_t cursor = 0;
    while ((this->board_.getGameState() & Board::IN_PROGRESS)
        == Board::IN_PROGRESS) {
        if (this->board_.getGameState() & Board::IN_CHECKMATE)
            throw Error(Error::PLAY_BEING_CHECKMATE);

        std::string currentMove;
        const bool lastMove =
            updateCursor(input, currentTotalMove, cursor, currentMove);
        this->applyMove(currentMove, currentTotalMove);
        if (!lastMove)
            return getGameState(input);
        currentTotalMove++;
    }
}

size_t ChessTrainer::Notation::PGN::readTags(const std::string& input) {
    bool tagOpened = false;
    bool tagContentOpened = false;
    std::string tagContent;
    std::string tagTitle;
    size_t skippingChars = 0;
    const auto& lines = ChessTrainer::Utils::splitString(input, '\n');
    bool mustStop = false;

    for (const auto& line: lines) {
        skippingChars += line.length() + 1;
        for (const auto& c: line) {
            if (c == '[') {
                if (tagOpened)
                    throw Error(Error::TAG_ALREADY_OPEN);
                tagOpened = true;
                continue;
            } else if (c == '\"') {
                if (!tagOpened)
                    throw Error(Error::TAG_NOT_OPEN);
                tagContentOpened = !tagContentOpened;
                continue;
            }
            if (c == ']') {
                if (!tagOpened)
                    throw Error(Error::TAG_EXTRA_CLOSING_TOKEN);
                tagOpened = false;
                this->tags_.emplace_back(tagTitle, tagContent);
                tagContent = "";
                tagTitle = "";
                continue;
            }
            if (!tagOpened && !tagContentOpened) {
                skippingChars -= line.length() + 1;
                mustStop = true;
                break;
            }
            if (tagContentOpened)
                tagContent += c;
            else if (!std::isspace(c))
                tagTitle += c;
        }
        if (mustStop)
            break;
    }
    if (tagContentOpened)
        throw Error(Error::TAG_QUOTE_UNCLOSED);
    if (tagOpened)
        throw Error(Error::TAG_NOT_CLOSED);
    for (const auto& rTag: ChessTrainer::Notation::PGN::required_tags_) {
        if (std::find_if(this->tags_.begin(),
                         this->tags_.end(),
                         [rTag](const GameTag& t) {
                             std::string tagName = t.first;
                             std::transform(tagName.begin(),
                                            tagName.end(),
                                            tagName.begin(),
                                            [](unsigned char c) {
                                                return std::tolower(c);
                                            });
                             return std::any_of(rTag.begin(),
                                                rTag.end(),
                                                [tagName](const std::string& tagAlternative) {
                                                    return tagAlternative ==
                                                        tagName;
                                                });
                         }) == this->tags_.end())
            throw Error(Error::TAG_MANDATORY_MISSING, rTag[0]);
    }
    return skippingChars;
}

void ChessTrainer::Notation::PGN::invalidate() {
    //std::cerr << "Invalid PGN: " << this->error_ << std::endl;
    //std::cerr << "FEN of the current position: "
    //          << Notation::FEN(this->board_, IPiece::White).getFen()
    //          << std::endl;
    this->tags_.clear();
    this->board_.clear();
}

bool ChessTrainer::Notation::PGN::isValid() const {
    return !this->error_;
}

ChessTrainer::Notation::PGN::PGN(const std::string& input)
    : board_(IPiece::Color::White), logger_("PGN", "pgn.log") {
    //printf("test: %i\n", this->board_.getTotalMoves());
    //printf("input: '%s'\n", input.c_str());
    try {
        std::size_t skippingChars = this->readTags(input);
        //std::cout << "Tags:" << std::endl;
        //for (const auto& t : this->tags_)
        //    std::cout << "['" << t.first << "' '" << t.second << "']" << std::endl;
        if (this->error_) {
            this->invalidate();
            return;
        }
        this->readMoves(input.substr(skippingChars));
        //std::cout << "FEN of the current position: "
        //          << Notation::FEN(this->board_, IPiece::White).getFen()
        //          << std::endl;
    } catch (const Error& err) {
        this->error_ = err;
        this->invalidate();
    }
}

const ChessTrainer::Board ChessTrainer::Notation::PGN::getBoard() const {
    return this->board_;
}

ChessTrainer::IPiece::shared_ptr
ChessTrainer::Notation::PGN::createPieceFromDiminutive(
    const ChessTrainer::IPiece::Color& color,
    char diminutive) {
    switch (diminutive) {
        case 'R':
            return std::make_shared<Rock>(color);
        case 'K':
            return std::make_shared<King>(color);
        case 'N':
            return std::make_shared<Knight>(color);
        case 'Q':
            return std::make_shared<Queen>(color);
        case 'B':
            return std::make_shared<Bishop>(color);
        default:
            return nullptr;
    }
}
const std::vector<ChessTrainer::Notation::PGN::GameTag>
ChessTrainer::Notation::PGN::getTags() const {
    return this->tags_;
}

ChessTrainer::Notation::PGN::PGN(const ChessTrainer::Notation::PGN& p)
    : logger_(p.logger_) {
    this->board_ = p.board_;
    this->tags_ = p.tags_;
    this->error_ = p.error_;
}

ChessTrainer::Notation::PGN::Error
ChessTrainer::Notation::PGN::getError() const {
    return this->error_;
}

void ChessTrainer::Notation::PGN::applyPromotion(const std::string& move,
                                                 ChessTrainer::IPiece::Color color) {
    //printf("move: '%s'\n", move.c_str());
    //this->logger_.Debug("Original move", move);
    //printf("movecpy: '%s'\n", moveCpy.c_str());

    const auto equalChar = move.find('=');
    const std::string rawCoordinates = move.substr(0, equalChar);
    //printf("raw: '%s'\n", rawCoordinates.c_str());
    Coordinates toCoord;
    Coordinates fromCoord;
    const auto takenChar = move.find('x');
    if (takenChar != std::string::npos) {
        const auto piece = this->getPieceDataFromNotation(move,
                                                          rawCoordinates,
                                                          color);
        toCoord = piece.coordinates;
        fromCoord = Coordinates(
            color == IPiece::Color::White ? std::string(1, piece.priorLine) +
                "7" : std::string(1, piece.priorLine) + "1");
    } else {
        toCoord = Coordinates(rawCoordinates);
        int moveIdx;
        if (color == IPiece::Color::Black)
            moveIdx = 1;
        else
            moveIdx = -1;
        fromCoord = Coordinates(toCoord.getX(), toCoord.getY() + moveIdx);
    }

    const auto& piece = this->board_.getPiece(fromCoord);
    if (!Pawn::isPawn(piece))
        throw Error(Error::NOT_PROMOTING_PAWN);
    if (piece.getColor() != color)
        throw Error(Error::WRONG_COLOR_PROMOTED_PAWN);

    auto promotedPiece = this->createPieceFromDiminutive(color,
                                                         move[equalChar + 1]);
    if (promotedPiece == nullptr)
        throw Error(Error::INVALID_PROMOTED_DIMINUTIVE);
    this->board_.setPiece(fromCoord, std::make_shared<ChessTrainer::IPiece>());
    this->board_.setPiece(toCoord, promotedPiece);
}

ChessTrainer::Notation::PGN::PGN() : logger_("PGN", "pgn.log") {
}
