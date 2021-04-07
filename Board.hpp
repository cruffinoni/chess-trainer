
#ifndef CHESSTRAINER__BOARD_HPP_
#define CHESSTRAINER__BOARD_HPP_

#include <vector>
#include <array>
#include "Pieces/IPiece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Rock.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"

/**
 * Ajouter les flags:
 * Castle: Q & K
 * State: check, checkmate & ended
 */

class Board {
    public:

    static const uint8_t BoardSize = 8;
    static const constexpr uint8_t TotalBoardSize = BoardSize * BoardSize;
    typedef std::array<std::shared_ptr<IPiece>, TotalBoardSize> rawBoard_t;

    struct Iterator {
        using shared_pointer = std::shared_ptr<IPiece>;
        using reference = Iterator&;
        using difference_type = std::ptrdiff_t;
        using value_type = Iterator;
        using iterator_category = std::random_access_iterator_tag;

        public:
        Iterator(const rawBoard_t & board, int idx) : board_(board), idx_(idx) {}

        Iterator& operator++() {
            idx_++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            idx_--;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator operator+(const int rhs) {
            this->idx_ += rhs;
            return *this;
        }

        reference operator+=(const int rhs) {
            this->idx_ += rhs;
            return *this;
        }

        std::pair<std::shared_ptr<IPiece>, int> operator*() {
            if (this->idx_ >= TotalBoardSize || this->idx_ < 0)
                throw std::out_of_range("invalid board range");
            return std::make_pair(this->board_[idx_], idx_);
        }

        bool operator==(const Iterator& a) const {
            return this->idx_ == a.idx_;
        }

        bool operator!=(const Iterator& a) const {
            return this->idx_ != a.idx_;
        }

        private:
        rawBoard_t board_;
        int idx_;
    };

    Board();
    explicit Board(const IPiece::Color& defaultBoardColor);
    Board(const Board::rawBoard_t& array);
    ~Board() = default;
    Board(const Board& b) = default;

    void print();

    bool movePiece(const Coordinates& from, const Coordinates& to);
    void setPiece(const Coordinates& pos, const std::shared_ptr<IPiece>& piece);
    bool canMove(const IPiece& piece, const Coordinates& to);
    void printAllMoves() const;
    void printLastMove() const;
    uint32_t countMove() const;
    [[nodiscard]] IPiece::Color getTurn() const;
    void setChessColorSide(const IPiece::Color& color);
    void setMinTotalMoves(uint16_t nb);
    uint32_t getTotalMoves() const;
    void clear();
    [[nodiscard]] rawBoard_t getRawBoard() const;

    Iterator begin() {
        return Iterator(this->board_, 0);
    }
    Iterator end() {
        return Iterator(this->board_, TotalBoardSize);
    }

    Iterator rbegin() {
        return Iterator(this->board_, TotalBoardSize - 1);
    }
    Iterator rend() {
        return Iterator(this->board_, -1);
    }

    private:
    void registerMove(const std::shared_ptr<IPiece>& piece,
                      const Coordinates& from,
                      const Coordinates& to,
                      bool take);
    static int getBoardIdxFromCoordinates(const Coordinates& pos);
    rawBoard_t board_;

    std::vector<std::pair<std::string, std::string>> move_;
    uint16_t totalMoves_;
    IPiece::Color chessSide_{IPiece::Color::White};
    void printWhiteSide();
    void printBlackSide();
};

#endif //CHESSTRAINER__BOARD_HPP_
