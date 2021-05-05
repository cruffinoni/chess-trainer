/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_PAWN_HPP_
#define CHESSTRAINER_PIECES_PAWN_HPP_

#include "IPiece.hpp"

namespace ChessTrainer {
    class Pawn : public IPiece {
        public:
        explicit Pawn(const Color& color) : IPiece("Pawn",
                                                   'P',
                                                   color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board) const override {
            const Coordinates c{fromIdx};
            const bool isWhite = this->color_ == IPiece::Color::White;
            std::vector<int> vec;
            int oneCase = isWhite ? fromIdx + ChessTrainer::Utils::BoardSize : fromIdx - ChessTrainer::Utils::BoardSize;

            if (oneCase > 0 && oneCase <= ChessTrainer::Utils::TotalBoardSize
                && !*board[oneCase])
                vec.emplace_back(oneCase);
            if (isWhite) {
                if (c.getY() == 2)
                    vec.emplace_back(Coordinates{c.getX(),
                                                 static_cast<uint8_t>(c.getY()
                                                     + 2u)}.toBoardIndex());
            } else {
                if (c.getY() == 7)
                    vec.emplace_back(Coordinates{c.getX(),
                                                 static_cast<uint8_t>(c.getY()
                                                     - 2u)}.toBoardIndex());
            }
            oneCase--;
            if (oneCase > 0 && oneCase <= ChessTrainer::Utils::TotalBoardSize && *board[oneCase])
                vec.emplace_back(oneCase);
            oneCase += 2;
            if (oneCase > 0 && oneCase <= ChessTrainer::Utils::TotalBoardSize && *board[oneCase])
                vec.emplace_back(oneCase);
            return vec;
        }
    };
}

#endif //CHESSTRAINER_PIECES_PAWN_HPP_
