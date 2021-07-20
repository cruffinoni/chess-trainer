/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_KNIGHT_HPP_
#define CHESSTRAINER_PIECES_KNIGHT_HPP_

#include "IPiece.hpp"

namespace ChessTrainer {
    class Knight : public IPiece {
        public:
        explicit Knight(const Color& color) : IPiece("Knight",
                                                     'N',
                                                     color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board,
                                                const helperPieceData& lastMove) const override {
            const Coordinates coord(fromIdx);
            std::vector<std::pair<int, int>> posAvailable = {
                {coord.getX() + 2, coord.getY() - 1},
                {coord.getX() + 2, coord.getY() + 1},
                {coord.getX() + 1, coord.getY() + 2},
                {coord.getX() - 1, coord.getY() + 2},
                {coord.getX() - 2, coord.getY() + 1},
                {coord.getX() - 2, coord.getY() - 1},
                {coord.getX() - 1, coord.getY() - 2},
                {coord.getX() + 1, coord.getY() - 2}
            };
            std::vector<int> legalPosition;
            for (const auto& p : posAvailable) {
                //printf("bidx: %i & %i\n", p.first, p.second);
                if (p.first >= Utils::BoardSize || p.first < 0 ||
                p.second > Utils::BoardSize || p.second < 0)
                    continue;
                try {
                    Coordinates c(p.first, p.second);
                    const int bIdx = c.toBoardIndex();
                    if (bIdx >= Utils::TotalBoardSize || bIdx < 0)
                        continue;
                    if (*board[bIdx]) {
                        if (board[bIdx]->getColor() != this->color_)
                            legalPosition.emplace_back(bIdx);
                    } else {
                        legalPosition.emplace_back(bIdx);
                    }
                } catch (const std::out_of_range& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            std::sort(legalPosition.begin(), legalPosition.end());
            //printf("From: %i\n", fromIdx);
            //for (const auto& v: legalPosition)
            //    std::cout << "v: " << v << std::endl;
            return legalPosition;
        }
    };
}

#endif //CHESSTRAINER_PIECES_KNIGHT_HPP_
