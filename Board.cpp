
#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Board.hpp"
#include "Shell/Notation/FEN.hpp"

Board::Board() {
    this->clear();
}

Board::Board(const IPiece::Color& defaultChessColor)
    : Board(ChessTrainer::Notation::FEN(ChessTrainer::Notation::FEN::DefaultBoard)
                .getBoard()) {
    this->chessSide_ = defaultChessColor;
}

void Board::printWhiteSide() {
    for (uint16_t row = 0; row != BoardSize + 1; ++row) {
        for (uint16_t column = 0; column != BoardSize + 1; ++column) {
            if (column == 0) {
                if (row == BoardSize)
                    std::cout << " |";
                else
                    std::cout << "\033[1;36m" << std::to_string(BoardSize - row)
                              << "\033[0m|";
            } else if (row == BoardSize) {
                std::cout << "\033[1;36m" << (char) ('a' + (column - 1))
                          << "\033[0m|";
            } else {
                auto board_idx =
                    (BoardSize - row) * BoardSize - (BoardSize - column + 1);
                std::cout << this->board_[board_idx]->getEmbeddedDiminutive()
                          << "|";
            }
        }
        std::cout << std::endl;
    }
}

void Board::printBlackSide() {
    for (uint16_t row = 0, x = BoardSize; row != BoardSize + 1; ++row, --x) {
        for (uint16_t column = 0, y = BoardSize; column != BoardSize + 1;
             ++column, --y) {
            if (column == 0) {
                if (row == BoardSize)
                    std::cout << " |";
                else
                    std::cout << "\033[1;36m"
                              << std::to_string((BoardSize + 1) - x)
                              << "\033[0m|";
            } else if (row == BoardSize) {
                std::cout << "\033[1;36m" << (char) ('a' + y)
                          << "\033[0m|";
            } else {
                auto board_idx = (row + 1) * Board::BoardSize - column;
                std::cout << this->board_[board_idx]->getEmbeddedDiminutive()
                          << "|";
            }
        }
        std::cout << std::endl;
    }
}

void Board::print() {
    if (this->chessSide_ == IPiece::Color::White)
        this->printWhiteSide();
    else
        this->printBlackSide();
}

bool Board::movePiece(const Coordinates& from, const Coordinates& to) {
    const auto idx_from = Board::getBoardIdxFromCoordinates(from);
    const auto idx_to = Board::getBoardIdxFromCoordinates(to);
    auto selectedPiece =
        this->board_[idx_from];
    if (!selectedPiece)
        return false;
    this->registerMove(selectedPiece,
                       from,
                       to,
                       (bool) this->board_[idx_to]);
    this->board_[idx_to] = this->board_[idx_from];
    this->board_[idx_from] = std::make_shared<IPiece>();
    return true;
}

void Board::registerMove(const std::shared_ptr<IPiece>& piece,
                         const Coordinates& from,
                         const Coordinates& to,
                         bool take) {
    std::string moveNotation;
    bool isPawn = piece->getName() == "Pawn";
    if (take) {
        moveNotation =
            (isPawn ? std::string(1, from.toStringNotation()[0]) : piece
                ->getStringDiminutive()) + "x" + to.toStringNotation();
        if (piece->getColor() == IPiece::Color::White)
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        else
            this->move_.back().second = moveNotation;
    } else {
        if (isPawn)
            moveNotation = to.toStringNotation();
        else
            moveNotation = piece->getStringDiminutive() + to.toStringNotation();
        if (piece->getColor() == IPiece::Color::White)
            this->move_.emplace_back(std::make_pair(moveNotation, ""));
        else
            this->move_.back().second = moveNotation;
    }
}
IPiece::Color Board::getTurn() const {
    if (this->move_.empty())
        return IPiece::Color::White;
    return !this->move_.back().first.empty()
               && !this->move_.back().second.empty() ? IPiece::Color::White
                                                     : IPiece::Color::Black;
}

void Board::printAllMoves() const {
    uint32_t count = 1;
    std::cout << "Total of " << this->move_.size() << " move(s):" << std::endl;
    for (const auto& i: this->move_)
        std::cout << count++ << ". " << std::setw(4) << std::right << i.first
                  << " " << std::setw(4) << std::right << i.second << std::endl;
}

void Board::printLastMove() const {
    std::cout << this->move_.size() << ". " << std::setw(4) << std::right
              << this->move_.back().first
              << " " << std::setw(4) << std::right << this->move_.back().second
              << std::endl;
}
uint32_t Board::countMove() const {
    return this->move_.size();
}
void Board::setChessColorSide(const IPiece::Color& color) {
    this->chessSide_ = color;
}

void Board::clear() {
    this->board_.fill(std::make_shared<IPiece>());
    this->move_.clear();
}

void Board::setPiece(const Coordinates& pos,
                     const std::shared_ptr<IPiece>& piece) {
    this->board_[Board::getBoardIdxFromCoordinates(pos)] = piece;
}

int Board::getBoardIdxFromCoordinates(const Coordinates& pos) {
    return pos.getX() + (pos.getY() - 1) * Board::BoardSize;
}

void Board::setMinTotalMoves(uint16_t nb) {
    this->totalMoves_ = nb;
}

uint32_t Board::getTotalMoves() const {
    return this->totalMoves_ + this->move_.size();
}

Board::rawBoard_t Board::getRawBoard() const {
    return this->board_;
}

Board::Board(const Board::rawBoard_t& array) {
    this->clear();
    this->board_ = array;
}

bool Board::canMove(const IPiece& piece, const Coordinates& to) {
    for (const auto& p: *this) {
        //std::cout << "Piece: " << *p.first << std::endl;
        if (*p.first != piece)
            continue;
        //std::cout << "Piece found " << *p.first << " at "
        //          << Coordinates(p.second) << " (" << p.second << ")"
        //          << std::endl;
        //std::cout << "User want to go at " << to << std::endl;
        //for (const auto& m: p.first->getMoves(p.second))
        //    std::cout << "m = " << m << std::endl;
        //std::cout << "Idx : " << p.second << std::endl;
        //std::cout << "To : "
        //          << ChessTrainer::Utils::generateBoardIdxFromCoord(to.getX(),
        //                                                            to.getY())
        //          << std::endl;

        const auto& availableCases = p.first->getMoves(p.second);
        const auto& canMove = std::find(availableCases.begin(),
                                        availableCases.end(),
                                        to);
        if (canMove != availableCases.end())
            return true;
    }
    return false;
}
