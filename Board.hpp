
#ifndef CHESSTRAINER__BOARD_HPP_
#define CHESSTRAINER__BOARD_HPP_

#include <memory>
#include <vector>
#include <array>
#include <iterator>
#include "Pieces/Coordinates.hpp"
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

namespace ChessTrainer {
    class Board {
        public:

        struct Iterator : std::iterator<std::forward_iterator_tag, Iterator> {
            using shared_pointer = std::shared_ptr<ChessTrainer::IPiece>;
            using reference = Iterator&;
            using difference_type = std::ptrdiff_t;
            using value_type = Iterator;
            using iterator_category = std::forward_iterator_tag;
            using value_dereference = std::pair<std::shared_ptr<ChessTrainer::IPiece>, int>;

            public:
            Iterator(const ChessTrainer::IPiece::rawBoard_t& board, int idx)
                : board_(board), idx_(idx) {}

            Iterator& operator++() {
                idx_++;
                return *this;
            }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            reference operator--() {
                idx_--;
                return *this;
            }

            const Iterator operator--(int) {
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

            reference operator+=(const Coordinates& rhs) {
                this->idx_ += rhs.toBoardIndex();
                return *this;
            }

            reference operator+=(Coordinates&& rhs) {
                this->idx_ += rhs.toBoardIndex();
                return *this;
            }

            std::pair<std::shared_ptr<ChessTrainer::IPiece>, int> operator*() {
                if (this->idx_ >= ChessTrainer::Utils::TotalBoardSize
                    || this->idx_ < 0)
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
            ChessTrainer::IPiece::rawBoard_t board_;
            int idx_;
        };

        Board();
        explicit Board(const ChessTrainer::IPiece::Color& defaultBoardColor);
        Board(const ChessTrainer::IPiece::rawBoard_t& array);
        ~Board() = default;
        Board(const Board& b) = default;

        void print() const;

        bool movePiece(const Coordinates& from,
                       const Coordinates& to,
                       bool registerMove = true);
        bool movePiece(const IPiece::helperPieceData& data,
                       bool registerMove = true);
        void setPiece(const Coordinates& pos,
                      const std::shared_ptr<ChessTrainer::IPiece>& piece);
        bool canMove(const ChessTrainer::IPiece& piece, const Coordinates& to);
        void printAllMoves() const;
        void printLastMove() const;
        uint32_t countMove() const;
        [[nodiscard]] ChessTrainer::IPiece::Color getTurn() const;
        void setChessColorSide(const ChessTrainer::IPiece::Color& color);
        void setMinTotalMoves(uint16_t nb);
        uint32_t getTotalMoves() const;
        void clear();
        [[nodiscard]] ChessTrainer::IPiece::rawBoard_t getRawBoard() const;

        // Game state
        typedef uint16_t gameState_t;
        enum gameState_e : gameState_t {
            NONE = 0,
            IN_PROGRESS = 0b1,
            ENDED = 0b10,

            // Who's the winner?
            WHITE = 0b100,
            BLACK = 0b1000,
            DRAW = 0b10000,

            // Early game ending?
            TIMEOUT = 0b100000,
            RESIGN = 0b1000000,

            // In game state check
            IN_CHECK = 0b10000000,
            IN_CHECKMATE = 0b100000000,
        };

        enum castleState_e : gameState_t {
            KINGSIDE_CASTLE = 0b1,
            QUEENSIDE_CASTLE = 0b10,
            LEFT_ROOK_FORBIDDEN = 0b100,
            RIGHT_ROOK_FORBIDDEN = 0b1000,
            KING_FORBIDDEN = 0b10000,
            CASTLE_FORBIDDEN = LEFT_ROOK_FORBIDDEN | RIGHT_ROOK_FORBIDDEN | KING_FORBIDDEN,
        };
        typedef std::array<gameState_t, 3> castleArray_t;

        void setGameState(gameState_t state);
        void addGameState(gameState_t state);
        void removeGameState(gameState_t state);
        [[nodiscard]] gameState_t getGameState() const;
        [[nodiscard]] std::string getGameStateName() const;
        bool doCastle(const ChessTrainer::Board::gameState_t castle,
                      const IPiece::Color color);
        [[nodiscard]] const castleArray_t& getCastleState() const;
        void setCastleState(const castleArray_t& state);

        // Iterator
        Iterator begin() {
            return Iterator(this->board_, 0);
        }
        Iterator end() {
            return Iterator(this->board_, ChessTrainer::Utils::TotalBoardSize);
        }

        Iterator rbegin() {
            return Iterator(this->board_,
                            ChessTrainer::Utils::TotalBoardSize - 1);
        }
        Iterator rend() {
            return Iterator(this->board_, -1);
        }
        void putLastTakes();
        void putLastTakes(uint16_t move);
        uint16_t getHalfmoveClock() const;
        void replayGame(bool stepBy = false) const;

        private:
        void registerMove(const IPiece::shared_ptr& piece,
                          const Coordinates& from,
                          const Coordinates& to,
                          bool take);
        static int getBoardIdxFromCoordinates(const Coordinates& pos);

        ChessTrainer::IPiece::rawBoard_t board_;
        std::vector<std::pair<std::string, std::string>> move_;
        uint16_t totalMoves_{};
        uint16_t lastTakes_ {};
        ChessTrainer::IPiece::helperPieceData lastMove_ = {
            .piece = nullptr,
            .allowEnPassant = false,
        };
        ChessTrainer::IPiece::Color
            chessSide_{ChessTrainer::IPiece::Color::White};
        void printWhiteSide() const;
        void printBlackSide() const;
        bool isKingsideCastleAvailable(const IPiece::Color color) const;
        bool isQueensideCastleAvailable(const IPiece::Color color) const;
        void doKingsideCastle(const IPiece::Color color);
        void doQueensideCastle(const IPiece::Color color);

        gameState_t state_{IN_PROGRESS};
        castleArray_t castle_ = {NONE, NONE, NONE};
    };

}

#endif //CHESSTRAINER__BOARD_HPP_
