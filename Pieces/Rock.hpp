
#ifndef CHESSTRAINER_PIECES_ROCK_HPP_
#define CHESSTRAINER_PIECES_ROCK_HPP_

#include <algorithm>
#include "IPiece.hpp"

namespace ChessTrainer {
    class Rock : public IPiece {
        public:
        explicit Rock(const Color& color) : IPiece("Rock",
                                                   'R',
                                                   color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board) const override {
            std::vector<int> vector;
            Coordinates pos(fromIdx);
            const int behind_x = fromIdx % 8;
            const int behind_y = fromIdx / 8;

            for (int i = 1; i <= behind_x; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() - i,
                    pos.getY());
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            for (int i = 1, j = 8 - behind_x; i < j; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() + i,
                    pos.getY());
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }

            for (int i = 1; i <= behind_y; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX(),
                    pos.getY() - i);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            for (int i = 1, j = 8 - behind_y; i < j; ++i) {
                const int idx = ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX(),
                    pos.getY() + i);
                if (board[idx]->getColor() != this->color_) {
                    vector.emplace_back(idx);
                    break;
                }
                vector.emplace_back(idx);
            }
            return vector;
        }
    };
}

#endif //CHESSTRAINER_PIECES_ROCK_HPP_
