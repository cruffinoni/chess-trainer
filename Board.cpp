
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include "Board.hpp"
#include "Shell/Notation/FEN.hpp"

ChessTrainer::Board::Board() {
    this->clear();
}

ChessTrainer::Board::Board(const ChessTrainer::IPiece::Color& defaultChessColor)
    : Board(ChessTrainer::Notation::FEN(ChessTrainer::Notation::FEN::DefaultBoard)
                .getBoard()) {
    this->chessSide_ = defaultChessColor;
}

void ChessTrainer::Board::printWhiteSide() const {
    for (uint16_t row = 0; row != ChessTrainer::Utils::BoardSize + 1; ++row) {
        for (uint16_t column = 0; column != ChessTrainer::Utils::BoardSize + 1;
             ++column) {
            if (column == 0) {
                if (row == ChessTrainer::Utils::BoardSize)
                    std::cout << " |";
                else
                    std::cout << "\033[1;36m" << std::to_string(
                        ChessTrainer::Utils::BoardSize - row)
                              << "\033[0m|";
            } else if (row == ChessTrainer::Utils::BoardSize) {
                std::cout << "\033[1;36m" << (char) ('a' + (column - 1))
                          << "\033[0m|";
            } else {
                auto board_idx =
                    (ChessTrainer::Utils::BoardSize - row)
                        * ChessTrainer::Utils::BoardSize
                        - (ChessTrainer::Utils::BoardSize - column + 1);
                std::cout << this->board_[board_idx]->getEmbeddedDiminutive()
                          << "|";
            }
        }
        std::cout << std::endl;
    }
}

void ChessTrainer::Board::printBlackSide() const {
    for (uint16_t row = 0, x = ChessTrainer::Utils::BoardSize;
         row != ChessTrainer::Utils::BoardSize + 1; ++row, --x) {
        for (uint16_t column = 0, y = ChessTrainer::Utils::BoardSize;
             column != ChessTrainer::Utils::BoardSize + 1;
             ++column, --y) {
            if (column == 0) {
                if (row == ChessTrainer::Utils::BoardSize)
                    std::cout << " |";
                else
                    std::cout << "\033[1;36m"
                              << std::to_string(
                                  (ChessTrainer::Utils::BoardSize + 1) - x)
                              << "\033[0m|";
            } else if (row == ChessTrainer::Utils::BoardSize) {
                std::cout << "\033[1;36m" << (char) ('a' + y)
                          << "\033[0m|";
            } else {
                auto board_idx =
                    (row + 1) * ChessTrainer::Utils::BoardSize - column;
                std::cout << this->board_[board_idx]->getEmbeddedDiminutive()
                          << "|";
            }
        }
        std::cout << std::endl;
    }
}

void ChessTrainer::Board::print() const {
    if (this->chessSide_ == ChessTrainer::IPiece::Color::White)
        this->printWhiteSide();
    else
        this->printBlackSide();
}

bool ChessTrainer::Board::movePiece(const IPiece::helperPieceData& data,
                                    bool registerMove) {
    const auto& color = data.piece->getColor();
    return std::any_of(this->begin(),
                       this->end(),
                       [&](const Iterator::value_dereference& val) {
                           if (*val.first != *data.piece)
                               return false;
                           if (val.first->getColor() != color)
                               return false;
                           const Coordinates from{val.second};
                           if (data.priorLine >= 0) {
                               if ((std::isdigit(data.priorLine)
                                   && from.getY() != (data.priorLine - '0')) ||
                                   from.getX() != (data.priorLine - 'a')) {
                                   return false;
                               }
                           }
                           const std::vector<int>& availableCases =
                               val.first->getMoves(val.second,
                                                   this->board_,
                                                   this->lastMove_);
                           const auto
                               movePieceCase = std::find(availableCases.begin(),
                                                         availableCases.end(),
                                                         data.coordinates);
                           if (movePieceCase == availableCases.end())
                               return false;
                           if (this->lastMove_.allowEnPassant
                               && !*this->board_[data.coordinates
                                   .toBoardIndex()]
                               && Pawn::isPawn(*data.piece)) {
                               if (Pawn::isTakeEnPassant(from.toBoardIndex(),
                                                         data.coordinates
                                                             .toBoardIndex())) {
                                   Coordinates c;
                                   if (data.piece->getColor() == IPiece::White)
                                       c = Coordinates(data.coordinates.getX(),
                                                       data.coordinates.getY()
                                                           - 1);
                                   else
                                       c = Coordinates(data.coordinates.getX(),
                                                       data.coordinates.getY()
                                                           + 1);
                                   this->board_[c.toBoardIndex()] =
                                       std::make_shared<ChessTrainer::IPiece>();
                               }
                           }
                           this->movePiece(from,
                                           data.coordinates,
                                           registerMove);
                           this->lastMove_ = data;
                           if (King::isKing(*data.piece))
                               this->castle_[data.piece->getColor()] |=
                                   CASTLE_FORBIDDEN;
                           if (Pawn::isPawn(*data.piece))
                               this->putLastTakes(0);
                           if (!this->isCastleSet(LEFT_ROOK_FORBIDDEN, data.piece->getColor()) && Rock::isRock(*data.piece)) {
                               if (data.piece->getColor() == IPiece::White && from == Coordinates("a1") ||
                               data.piece->getColor() == IPiece::Black && from == Coordinates("a8"))
                                   this->castle_[data.piece->getColor()] |= LEFT_ROOK_FORBIDDEN;
                           }
                           if (!this->isCastleSet(RIGHT_ROOK_FORBIDDEN, data.piece->getColor()) && Rock::isRock(*data.piece)) {
                               if (data.piece->getColor() == IPiece::White && from == Coordinates("h1") ||
                               data.piece->getColor() == IPiece::Black && from == Coordinates("h8"))
                                   this->castle_[data.piece->getColor()] |= RIGHT_ROOK_FORBIDDEN;
                           }

                           this->lastMove_.allowEnPassant =
                               Pawn::isPawn(*data.piece) && (
                                   abs(from.getY() - data.coordinates.getY())
                                       == 2);
                           return true;
                       }
    );
}

bool ChessTrainer::Board::movePiece(const Coordinates& from,
                                    const Coordinates& to,
                                    bool registerMove) {
    const auto idx_from = ChessTrainer::Board::getBoardIdxFromCoordinates(from);
    const auto idx_to = ChessTrainer::Board::getBoardIdxFromCoordinates(to);
    auto selectedPiece =
        this->board_[idx_from];
    if (!*selectedPiece)
        return false;
    if (registerMove)
        this->registerMove(selectedPiece,
                           from,
                           to,
                           (bool) *this->board_[idx_to]);
    this->board_[idx_to] = this->board_[idx_from];
    this->board_[idx_from] = std::make_shared<ChessTrainer::IPiece>();
    return true;
}

void ChessTrainer::Board::registerMove(const IPiece::shared_ptr& piece,
                                       const Coordinates& from,
                                       const Coordinates& to,
                                       bool take) {
    std::string moveNotation;
    if (take) {
        moveNotation =
            (Pawn::isPawn(*piece) ? std::string(1, from.toStringNotation()[0]) : piece
                ->getStringDiminutive()) + "x" + to.toStringNotation();
        if (piece->getColor() == ChessTrainer::IPiece::Color::White) {
            //std::cout << "white move" << std::endl;
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        }
        else {
            //std::cout << "black move" << std::endl;
            //printf("take => Move: %i\n", this->totalMoves_);
            this->totalMoves_++;
            //printf("take => Move2: %i\n", this->totalMoves_);
            this->move_.back().second = moveNotation;
        }
        this->putLastTakes(0);
    } else {
        if (Pawn::isPawn(*piece))
            moveNotation = to.toStringNotation();
        else
            moveNotation = piece->getStringDiminutive() + to.toStringNotation();
        if (piece->getColor() == ChessTrainer::IPiece::Color::White) {
            //std::cout << "white move" << std::endl;
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        }
        else {
            //std::cout << "black move" << std::endl;
            //printf("Move: %i\n", this->totalMoves_);
            this->totalMoves_++;
            //printf("Move2: %i\n", this->totalMoves_);
            this->move_.back().second = moveNotation;
        }
        this->lastTakes_++;
    }
}
ChessTrainer::IPiece::Color ChessTrainer::Board::getTurn() const {
    if (this->move_.empty())
        return ChessTrainer::IPiece::Color::White;
    return !this->move_.back().first.empty()
               && !this->move_.back().second.empty()
           ? ChessTrainer::IPiece::Color::White
           : ChessTrainer::IPiece::Color::Black;
}

void ChessTrainer::Board::printAllMoves() const {
    uint32_t count = 1;
    std::cout << "Total of " << this->move_.size() << " move(s):" << std::endl;
    for (const auto& i: this->move_)
        std::cout << count++ << ". " << std::setw(4) << std::right << i.first
                  << " " << std::setw(4) << std::right << i.second << std::endl;
}

void ChessTrainer::Board::printLastMove() const {
    std::cout << this->move_.size() << ". " << std::setw(4) << std::right
              << this->move_.back().first
              << " " << std::setw(4) << std::right << this->move_.back().second
              << std::endl;
}
uint32_t ChessTrainer::Board::countMove() const {
    return this->move_.size();
}
void ChessTrainer::Board::setChessColorSide(const ChessTrainer::IPiece::Color& color) {
    this->chessSide_ = color;
}

void ChessTrainer::Board::clear() {
    this->board_.fill(std::make_shared<ChessTrainer::IPiece>());
    this->move_.clear();
}

void ChessTrainer::Board::setPiece(const Coordinates& pos,
                                   const std::shared_ptr<ChessTrainer::IPiece>& piece) {
    this->board_[ChessTrainer::Board::getBoardIdxFromCoordinates(pos)] = piece;
}

int ChessTrainer::Board::getBoardIdxFromCoordinates(const Coordinates& pos) {
    return pos.getX() + (pos.getY() - 1) * ChessTrainer::Utils::BoardSize;
}

void ChessTrainer::Board::setMinTotalMoves(uint16_t nb) {
    this->totalMoves_ = nb;
}

uint32_t ChessTrainer::Board::getTotalMoves() const {
    //printf("total: %i & move: %zu\n", this->totalMoves_, this->move_.size());
    return this->totalMoves_;
}

ChessTrainer::IPiece::rawBoard_t ChessTrainer::Board::getRawBoard() const {
    return this->board_;
}

ChessTrainer::Board::Board(const ChessTrainer::IPiece::rawBoard_t& array) {
    this->clear();
    this->board_ = array;
}

bool ChessTrainer::Board::canMove(const ChessTrainer::IPiece& piece,
                                  const Coordinates& to) {
    return std::any_of(this->begin(),
                       this->end(),
                       [&](const Iterator::value_dereference& val) {
                           if (*val.first != piece)
                               return false;
                           const auto& availableCases =
                               val.first->getMoves(val.second,
                                                   this->board_, {});
                           return std::find(availableCases.begin(),
                                            availableCases.end(),
                                            to) != availableCases.end();
                       });
}

ChessTrainer::Board::gameState_t ChessTrainer::Board::getGameState() const {
    return this->state_;
}

void ChessTrainer::Board::setGameState(ChessTrainer::Board::gameState_t state) {
    this->state_ = state;
}

void ChessTrainer::Board::addGameState(ChessTrainer::Board::gameState_t state) {
    this->state_ |= state;
}

void ChessTrainer::Board::removeGameState(ChessTrainer::Board::gameState_t state) {
    this->state_ &= ~state;
}

std::string ChessTrainer::Board::getGameStateName() const {
    if (this->state_ & gameState_e::IN_PROGRESS)
        return "In progress";
    else if (this->state_ & gameState_e::DRAW)
        return "Draw";
    else if (this->state_ & gameState_e::ENDED) {
        if (this->state_ & gameState_e::WHITE)
            return "White won";
        else
            return "Black won";
    }
    return "(unknown state)";
}

bool ChessTrainer::Board::doCastle(const ChessTrainer::Board::gameState_t castle,
                                   const IPiece::Color color) {
    if (this->castle_[color] & castle) {
        std::cerr << "Can't castle multiple times" << std::endl;
        return false;
    }
    if (this->castle_[color] & CASTLE_FORBIDDEN) {
        std::cerr << "Castle is forbidden for this player" << std::endl;
        return false;
    }
    if (castle == KINGSIDE_CASTLE) {
        if (!isKingsideCastleAvailable(color)) {
            std::cout
                << "(KS) there is piece between the king and the rook : castle invalid"
                << std::endl;
            return false;
        }
        this->doKingsideCastle(color);
        this->castle_[color] |= CASTLE_FORBIDDEN;
        if (color == IPiece::White)
            this->move_.emplace_back(std::make_pair("O-O", ""));
        else
            this->move_.back().second = "O-O";
    } else {
        if (!isQueensideCastleAvailable(color)) {
            std::cout
                << "(QS) there is piece between the king and the rook : castle invalid"
                << std::endl;
            return false;
        }
        this->doQueensideCastle(color);
        this->castle_[color] |= CASTLE_FORBIDDEN;
        if (color == IPiece::White)
            this->move_.emplace_back(std::make_pair("O-O-O", ""));
        else
            this->move_.back().second = "O-O-O";
    }
    return true;
}

bool ChessTrainer::Board::isKingsideCastleAvailable(const IPiece::Color color) const {
    auto cs =
        color == IPiece::White ? Coordinates("e1").toBoardIndex() : Coordinates(
            "e8").toBoardIndex();
    return !*this->board_[cs + 1] && !*this->board_[cs + 2];
}

bool ChessTrainer::Board::isQueensideCastleAvailable(const IPiece::Color color) const {
    auto cs =
        color == IPiece::White ? Coordinates("a1").toBoardIndex() : Coordinates(
            "a8").toBoardIndex();
    bool valid = true;
    for (int i = 1; i < 3; ++i)
        if (*this->board_[cs + i])
            valid = false;
    return valid;
}

void ChessTrainer::Board::doKingsideCastle(const ChessTrainer::IPiece::Color color) {
    if (color == IPiece::White) {
        this->movePiece(Coordinates("e1"), Coordinates("g1"), false);
        this->movePiece(Coordinates("h1"), Coordinates("f1"), false);
    } else {
        this->movePiece(Coordinates("e8"), Coordinates("g8"), false);
        this->movePiece(Coordinates("h8"), Coordinates("f8"), false);
    }
}

void ChessTrainer::Board::doQueensideCastle(const ChessTrainer::IPiece::Color color) {
    if (color == IPiece::White) {
        this->movePiece(Coordinates("e1"), Coordinates("c1"), false);
        this->movePiece(Coordinates("a1"), Coordinates("d1"), false);
    } else {
        this->movePiece(Coordinates("e8"), Coordinates("c8"), false);
        this->movePiece(Coordinates("a8"), Coordinates("d8"), false);
    }
}

const ChessTrainer::Board::castleArray_t& ChessTrainer::Board::getCastleState() const {
    return this->castle_;
}

void ChessTrainer::Board::setCastleState(const ChessTrainer::Board::castleArray_t& state) {
    this->castle_ = state;
}

void ChessTrainer::Board::putLastTakes(uint16_t move) {
    this->lastTakes_ = move;
}
uint16_t ChessTrainer::Board::getHalfmoveClock() const {
    return this->lastTakes_;
}
void ChessTrainer::Board::replayGame(bool stepBy) const {
    //Board b(this->chessSide_);
    //std::for_each(this->move_.begin(), this->move_.end(), [&](const Move& m) {
    //    b.movePiece(m.from, m.to, false);
    //    if (stepBy || b.getTurn()
    //        == ChessTrainer::IPiece::Color::White) {
    //        b.printLastMove();
    //        b.print();
    //    }
    //});
}

ChessTrainer::IPiece::helperPieceData ChessTrainer::Board::getLastMovePiece() const {
    return this->lastMove_;
}

ChessTrainer::Board::Board(const ChessTrainer::Board& b) {
    this->lastMove_ = b.lastMove_;
    this->lastTakes_ = b.lastTakes_;
    this->castle_ = b.castle_;
    this->board_ = b.board_;
    this->state_ = b.state_;
    this->chessSide_ = b.chessSide_;
    this->move_ = b.move_;
    this->totalMoves_ = b.totalMoves_;
}

bool ChessTrainer::Board::isCastleSet(Board::castleState_e castle, const IPiece::Color color) const {
    return this->castle_[color] & castle;
}
