
#ifndef CHESSTRAINER_PIECES_ROCK_HPP_
#define CHESSTRAINER_PIECES_ROCK_HPP_

#include <algorithm>
#include "IPiece.hpp"

class Rock : public IPiece {
    public:
    explicit Rock(const Color& color) : IPiece("Rock",
                                               'R',
                                               color) {};
    [[nodiscard]] std::vector<int> getMoves(int fromIdx) const override {
        std::vector<int> vector;
        Coordinates pos(fromIdx);
        const int behind_x = fromIdx % 8;
        const int behind_y = fromIdx / 8;

        for (int i = 1; i <= behind_x; ++i) {
            vector.emplace_back(ChessTrainer::Utils::generateBoardIdxFromCoord(
                pos.getX() - i,
                pos.getY()));
        }
        for (int i = 1, j = 8 - behind_x; i < j; ++i) {
            vector.emplace_back(ChessTrainer::Utils::generateBoardIdxFromCoord(
                pos.getX() + i,
                pos.getY()));
        }

        for (int i = 1; i <= behind_y; ++i) {
            vector.emplace_back(ChessTrainer::Utils::generateBoardIdxFromCoord(
                pos.getX(),
                pos.getY() - i));
        }
        for (int i = 1, j = 8 - behind_y; i < j; ++i) {
            vector.emplace_back(ChessTrainer::Utils::generateBoardIdxFromCoord(
                pos.getX(),
                pos.getY() + i));
        }
        return vector;
    }
};

#endif //CHESSTRAINER_PIECES_ROCK_HPP_
