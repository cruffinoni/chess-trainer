
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
        for (const auto& vgs : validGameState) {
            const auto& endgame = input.find(vgs);
            if (endgame == std::string::npos)
                continue;
            buffer = input.substr(startIdx, endgame - (startIdx + 1));
            startIdx = endgame;
            //printf("[%i/endgame] Move found: '%s'\n",
            //       currentMove,
            //       buffer.c_str());
            return false;
        }
        return false;
    }
    buffer = input.substr(startIdx, moveFound - (startIdx + 1));
    //printf("[%i] Move found: '%s'\n",
    //       currentMove,
    //       buffer.c_str());
    startIdx = moveFound;
    return true;
}

void ChessTrainer::Notation::PGN::getGameState(
    const std::string& input) {
    const static std::vector<std::pair<std::string, Board::gameState_t>>
        validGameState = {
        {"1/2-1/2", Board::ENDED | Board::DRAW},
        {"1-0", Board::ENDED | Board::WHITE},
        {"0-1", Board::ENDED | Board::BLACK},
        {"*", Board::IN_PROGRESS},
    };
    for (const auto& s: validGameState) {
        const auto& m = input.find(s.first);
        if (m != std::string::npos) {
            if (m + s.first.size() != input.size())
                throw Error(Error::GAME_RESULT_INVALID_PLACEMENT);
            this->board_.setGameState(s.second);
            std::cout << "Last move detected ; state of the game -> "
                      << this->board_.getGameStateName() << std::endl;
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
    const static auto
        removePart = [&buffer](const std::string& toRemove) -> void {
        size_t start = buffer.find(toRemove);
        if (start != std::string::npos)
            buffer.erase(start, toRemove.length());
    };
    removePart(std::to_string(move) + ".");
    removePart(std::to_string(move) + "...");
}

void ChessTrainer::Notation::PGN::checkForCheckOrMate(std::string& buffer) {
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

ChessTrainer::IPiece::helperPieceData ChessTrainer::Notation::PGN::getPieceDataFromNotation(
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


std::optional<ChessTrainer::IPiece::helperPieceData> ChessTrainer::Notation::PGN::checkForTakeMove(
    const std::string& originalMove,
    std::string& move,
    const ChessTrainer::IPiece::Color& color) {
    const auto& takeIdx = move.find_first_of('x');
    // Bxb5
    if (takeIdx == std::string::npos)
        return std::nullopt;
    move.erase(takeIdx, 1);
    return getPieceDataFromNotation(originalMove, move, color);
    //pieceData p {
    //    .piece = std::make_shared<Pawn>(color),
    //    .coordinates = Coordinates(move.substr(move.length() - 2)),
    //    .priorLine = -1
    //};
    //const auto firstPart = move.substr(0, takeIdx);
    //printf("Fp: '%s'\n", firstPart.c_str());
    //if (firstPart.length() > 1) {
    //    p.piece = createPieceFromDiminutive(color, firstPart[0]);
    //    if (p.piece == nullptr)
    //        throw Error(Error::UNKNOWN_PIECE, move);
    //} else {
    //    p.priorLine = firstPart[0];
    //}
    //
    //std::cout << "Piece detected: " << p.piece->getName() << std::endl;
    //// Rbxe2 Rbe2
    //if (firstPart.length() == 2)
    //    p.priorLine = firstPart[1];
    //else if (firstPart.length() > 2)
    //    std::cerr << move << " seems invalid" << std::endl;
    //std::cout << "Taking piece off idx: '" << move << "'" << std::endl;
    //return p;
}

ChessTrainer::IPiece::helperPieceData ChessTrainer::Notation::PGN::getPiece(std::string move,
                                                                            const IPiece::Color& color) {
    const std::string& cpy = move.substr();
    this->checkForCheckOrMate(move);
    const auto& takingPiece =
        ChessTrainer::Notation::PGN::checkForTakeMove(cpy,
                                                      move,
                                                      color);
    if (takingPiece.has_value()) {
        return takingPiece.value();
    }
    //const auto& pieceIdx = move.find_first_of("RQNKB");
    //const Coordinates toCoord{move.substr(move.length() - 2)};
    ////printf("Coordinates to => '%s'\n", toCoord.toStringNotation().c_str());
    //if (pieceIdx == std::string::npos) {
    //    return pieceData{std::make_shared<Pawn>(color), toCoord, -1};
    //}
    //const auto& piece = ChessTrainer::Notation::PGN::createPieceFromDiminutive(
    //    color,
    //    move[pieceIdx]);
    //if (piece == nullptr)
    //    throw Error(Error::UNKNOWN_PIECE, move);
    //return pieceData{piece, toCoord, -1};
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

void ChessTrainer::Notation::PGN::applyMove(const std::string& move,
                                            int currentMove) {
    auto moveCpy = move.substr();
    removeComments(moveCpy);
    //printf("After removing comments: '%s'\n", moveCpy.c_str());
    this->removeRecurrentMoveNumber(moveCpy, currentMove);
    //printf("After recurrent move numbers: '%s'\n", moveCpy.c_str());
    const auto& vector = Utils::splitStringBySpace(moveCpy);
    std::vector<std::string> rawCoordinates;
    for (const auto& v: vector)
        if (!v.empty())
            rawCoordinates.push_back(v);
    if (rawCoordinates.size() > 2) {
        //std::cerr << "move " << move << std::endl;
        throw Error(Error::INVALID_NUMBER_OF_COORDINATES, move);
    }

    IPiece::Color currColor = IPiece::Color::White;
    for (auto& rc: rawCoordinates) {
        const auto& castleType = getCastleType(rc, currColor);
        if (castleType != Board::NONE) {
            //std::bitset<12> b (castleType);
            if (!this->board_.doCastle(castleType, currColor)) {
                std::ostringstream o;
                o << "for " << currColor << " at " << rc;
                throw Error(Error::INVALID_CASTLE, o.str());
            }
        } else {
            const auto& piece = getPiece(rc, currColor);
            //std::cout << "Move " <<  rc << std::endl;
            //if (piece.priorLine > 0)
            //    printf("Prioritized line: %c\n", piece.priorLine);
            //else
            //    printf("Prioritized line: %i\n", piece.priorLine);
            //std::cout << "Piece: " << *piece.piece << " to -> "
            //          << piece.coordinates << std::endl;
            if (!this->board_.movePiece(piece)) {
                //this->board_.print();
                throw Error(Error::ILLEGAL_MOVE, rc);
            }
        }
        currColor = IPiece::Color::Black;
    }
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
                break;
            }
            if (tagContentOpened)
                tagContent += c;
            else if (!std::isspace(c))
                tagTitle += c;
        }
    }
    if (tagContentOpened)
        throw Error(Error::TAG_QUOTE_UNCLOSED);
    if (tagOpened)
        throw Error(Error::TAG_NOT_CLOSED);
    for (const auto& rTag : ChessTrainer::Notation::PGN::required_tags_) {
        if (std::find_if(this->tags_.begin(),
                         this->tags_.end(),
                         [rTag](const tag& t) {
                             std::string tagName = t.first;
                             std::transform(tagName.begin(),
                                            tagName.end(),
                                            tagName.begin(),
                                            [](unsigned char c) {
                                                return std::tolower(c);
                                            });
                             return std::any_of(rTag.begin(), rTag.end(), [tagName](const std::string& tagAlternative) {
                                 return tagAlternative == tagName;
                             });
                         }) == this->tags_.end())
            throw Error(Error::TAG_MANDATORY_MISSING, rTag[0]);
    }
    return skippingChars;
}

void ChessTrainer::Notation::PGN::invalidate() {
    std::cerr << "Invalid PGN: " << this->error_ << std::endl;
    std::cerr << "FEN of the current position: "
              << Notation::FEN(this->board_, IPiece::White).getFen()
              << std::endl;
    this->tags_.clear();
    this->board_.clear();
}

bool ChessTrainer::Notation::PGN::isValid() const {
    return this->error_;
}

ChessTrainer::Notation::PGN::PGN(const std::string& input)
    : board_(IPiece::Color::White) {

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
        std::cout << "FEN of the current position: "
              << Notation::FEN(this->board_, IPiece::White).getFen()
              << std::endl;
    } catch (const Error& err) {
        this->error_ = err;
        this->invalidate();
    }
}

const ChessTrainer::Board ChessTrainer::Notation::PGN::getBoard() const {
    return this->board_;
}

ChessTrainer::IPiece::shared_ptr ChessTrainer::Notation::PGN::createPieceFromDiminutive(
    const ChessTrainer::IPiece::Color& color,
    char diminutive) {
    switch (diminutive) {
        case 'R':return std::make_shared<Rock>(color);
        case 'K':return std::make_shared<King>(color);
        case 'N':return std::make_shared<Knight>(color);
        case 'Q':return std::make_shared<Queen>(color);
        case 'B':return std::make_shared<Bishop>(color);
        default:return nullptr;
    }
}
