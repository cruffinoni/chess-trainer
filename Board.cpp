
#include <iostream>
#include <iomanip>
#include <cstdint>
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

bool ChessTrainer::Board::movePiece(const Coordinates& from,
                                    const Coordinates& to) {
    const auto idx_from = ChessTrainer::Board::getBoardIdxFromCoordinates(from);
    const auto idx_to = ChessTrainer::Board::getBoardIdxFromCoordinates(to);
    auto selectedPiece =
        this->board_[idx_from];
    if (!selectedPiece)
        return false;
    this->registerMove(selectedPiece,
                       from,
                       to,
                       (bool) this->board_[idx_to]);
    this->board_[idx_to] = this->board_[idx_from];
    this->board_[idx_from] = std::make_shared<ChessTrainer::IPiece>();
    return true;
}

void ChessTrainer::Board::registerMove(const std::shared_ptr<ChessTrainer::IPiece>& piece,
                                       const Coordinates& from,
                                       const Coordinates& to,
                                       bool take) {
    std::string moveNotation;
    bool isPawn = piece->getName() == "Pawn";
    if (take) {
        moveNotation =
            (isPawn ? std::string(1, from.toStringNotation()[0]) : piece
                ->getStringDiminutive()) + "x" + to.toStringNotation();
        if (piece->getColor() == ChessTrainer::IPiece::Color::White)
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        else
            this->move_.back().second = moveNotation;
    } else {
        if (isPawn)
            moveNotation = to.toStringNotation();
        else
            moveNotation = piece->getStringDiminutive() + to.toStringNotation();
        if (piece->getColor() == ChessTrainer::IPiece::Color::White)
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        else
            this->move_.back().second = moveNotation;
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
    return this->totalMoves_ + this->move_.size();
}

ChessTrainer::IPiece::rawBoard_t ChessTrainer::Board::getRawBoard() const {
    return this->board_;
}

ChessTrainer::Board::Board(const ChessTrainer::IPiece::rawBoard_t& array) {
    this->clear();
    this->board_ = array;
}

bool ChessTrainer::Board::movePiece(const ChessTrainer::IPiece& piece,
                                    const ChessTrainer::Coordinates& to) {
    for (const auto& p: *this) {
        if (*p.first != piece)
            continue;
        const auto& availableCases = p.first->getMoves(p.second,
                                                       this->board_);
        const auto& canMove = std::find(availableCases.begin(),
                                        availableCases.end(),
                                        to);
        if (canMove == availableCases.end())
            continue;
        this->movePiece(Coordinates(p.second), to);
        return true;
    }
    return false;
}


bool ChessTrainer::Board::canMove(const ChessTrainer::IPiece& piece,
                                  const Coordinates& to) {
    for (const auto& p: *this) {
        //std::cout << "Piece: " << *p.first << std::endl;
        if (*p.first != piece)
            continue;
        //std::cout << "Piece found " << *p.first << " at "
        //          << Coordinates(p.second) << " (" << p.second << ")"
        //          << std::endl;
        //std::cout << "User want to go at " << to << std::endl;
        //for (const auto& m: p.first->getMoves(p.second, this->board_))
        //    std::cout << "m = " << m << std::endl;
        //std::cout << "Idx : " << p.second << std::endl;
        //std::cout << "To : "
        //          << ChessTrainer::Utils::generateBoardIdxFromCoord(to.getX(),
        //                                                            to.getY())
        //          << std::endl;

        //std::cout << "Ggo to " << ChessTrainer::Utils::generateBoardIdxFromCoord(to.getX(), to.getY()) << std::endl;
        const auto& availableCases = p.first->getMoves(p.second,
                                                       this->board_);
        const auto& canMove = std::find(availableCases.begin(),
                                        availableCases.end(),
                                        to) != availableCases.end();
        if (canMove)
            return true;
    }
    return false;
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
