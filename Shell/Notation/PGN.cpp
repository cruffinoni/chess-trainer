
#include <algorithm>
#include "PGN.hpp"

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
            printf("[%i/endgame] Move found: '%s'\n",
                   currentMove,
                   buffer.c_str());
            return false;
        }
        return false;
    }
    buffer = input.substr(startIdx, moveFound - (startIdx + 1));
    printf("[%i] Move found: '%s'\n",
           currentMove,
           buffer.c_str());
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

void ChessTrainer::Notation::PGN::removeCheckOrMate(std::string& buffer) {
    const auto& pieceIdx = buffer.find_first_of("+#");
    if (pieceIdx == std::string::npos)
        return;
    if (buffer[pieceIdx] == '+') {
        this->board_.addGameState(Board::IN_CHECK);
        printf("[c/m] in check\n");
    } else {
        this->board_.addGameState(Board::IN_CHECKMATE);
        printf("[c/m] checkmate\n");
    }
    buffer.erase(pieceIdx, 1);
}

ChessTrainer::Notation::PGN::pieceData ChessTrainer::Notation::PGN::getPiece(std::string& move,
                                                                             const ChessTrainer::IPiece::Color& color) {
    //printf("move: '%s'\n", move.c_str());
    this->removeCheckOrMate(move);
    const auto& pieceIdx = move.find_first_of("RQNKB");
    const Coordinates toCoord{move.substr(move.length() - 2)};
    //printf("Coordinates to => '%s'\n", toCoord.toStringNotation().c_str());
    if (pieceIdx == std::string::npos) {
        return std::make_pair(std::make_shared<Pawn>(color), toCoord);
    }
    //printf("Piece: %i => %c\n", pieceIdx, move[pieceIdx]);
    switch (move[pieceIdx]) {
        case 'R': return std::make_pair(std::make_shared<Rock>(color), toCoord);
        case 'K': return std::make_pair(std::make_shared<King>(color), toCoord);
        case 'N':
            return std::make_pair(std::make_shared<Knight>(color),
                                  toCoord);
        case 'Q':
            return std::make_pair(std::make_shared<Queen>(color),
                                  toCoord);
        case 'B':
            return std::make_pair(std::make_shared<Bishop>(color),
                                  toCoord);
    }
    throw Error(Error::UNKNOWN_PIECE, move);
}

void ChessTrainer::Notation::PGN::applyMove(const std::string& move,
                                            int currentMove) {
    auto moveCpy = move.substr();
    removeComments(moveCpy);
    //printf("After removing comments: '%s'\n", moveCpy.c_str());
    this->removeRecurrentMoveNumber(moveCpy, currentMove);
    //printf("After recurrent move numbers: '%s'\n", moveCpy.c_str());
    const auto& vector = Utils::splitString(moveCpy, ' ');
    std::vector<std::string> rawCoordinates;
    for (const auto& v: vector)
        if (!v.empty())
            rawCoordinates.push_back(v);
    if (rawCoordinates.size() != 2)
        throw Error(Error::INVALID_NUMBER_OF_COORDINATES, move);

    IPiece::Color currColor = IPiece::Color::White;
    for (auto& rc: rawCoordinates) {
        const auto& piece = getPiece(rc, currColor);
        //std::cout << "Piece detected '" << *piece.first << "' at "
        //          << piece.second << std::endl;
        try {
            if (!this->board_.movePiece(*piece.first, piece.second))
                throw Error(Error::ILLEGAL_MOVE, rc);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        currColor = IPiece::Color::Black;
    }
}

void ChessTrainer::Notation::PGN::readMoves(const std::string& input) {
    int currentTotalMove = 1;
    size_t cursor = 0;
    while (this->board_.getGameState() == Board::IN_PROGRESS) {
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
        std::string strTag = rTag;
        if (std::find_if(this->tags_.begin(),
                         this->tags_.end(),
                         [strTag](const tag& t) {
                             std::string tagName = t.first;
                             std::transform(tagName.begin(),
                                            tagName.end(),
                                            tagName.begin(),
                                            [](unsigned char c) {
                                                return std::tolower(c);
                                            });
                             return tagName == strTag;
                         }) == this->tags_.end())
            throw Error(Error::TAG_MANDATORY_MISSING, strTag);
    }
    return skippingChars;
}

void ChessTrainer::Notation::PGN::invalidate() {
    std::cerr << "Invalid PGN: " << this->error_ << std::endl;
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
    } catch (const Error& err) {
        this->error_ = err;
        this->invalidate();
    }
}

const ChessTrainer::Board ChessTrainer::Notation::PGN::getBoard() const {
    return this->board_;
}
