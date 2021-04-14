
#ifndef CHESSTRAINER_PIECES_BISHOP_HPP_
#define CHESSTRAINER_PIECES_BISHOP_HPP_

#include "IPiece.hpp"

namespace ChessTrainer {
    class Bishop : public IPiece {
        public:
        explicit Bishop(const Color& color) : IPiece("Bishop",
                                                     'B',
                                                     color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board) const override {
            std::vector<int> vector;
            Coordinates pos(fromIdx);
            const int up = fromIdx % 8;
            const int down = fromIdx / 8;
            //printf("From idx: %i w/ %i & %i\n", fromIdx, up, down);

            for (int i = 1; i <= up; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() - i,
                    pos.getY() - i);
                if (idx < 0 || idx >= ChessTrainer::Utils::TotalBoardSize)
                    continue;
                printf("A: Index: %i\n", idx);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            for (int i = 1, j = 8 - up; i < j; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() + i,
                    pos.getY() + i);
                if (idx < 0 || idx >= ChessTrainer::Utils::TotalBoardSize)
                    continue;
                printf("B: Index: %i\n", idx);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            for (int i = 1, j = 8 - down; i < j; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() - i,
                    pos.getY() + i);
                if (idx < 0 || idx >= ChessTrainer::Utils::TotalBoardSize)
                    continue;
                printf("C: Index: %i\n", idx);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            for (int i = 1, j = 8 - up; i < j; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() + i,
                    pos.getY() - i);
                if (idx < 0 || idx >= ChessTrainer::Utils::TotalBoardSize)
                    continue;
                printf("D: Index: %i\n", idx);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            return vector;
        };
    };
}

#endif //CHESSTRAINER_PIECES_BISHOP_HPP_
