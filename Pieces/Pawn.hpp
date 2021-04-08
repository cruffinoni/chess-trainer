/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_PAWN_HPP_
#define CHESSTRAINER_PIECES_PAWN_HPP_

#include "IPiece.hpp"

class Pawn : public IPiece {
    public:
    explicit Pawn(const Color& color) : IPiece("Pawn",
                                               'P',
                                               color) {};
    [[nodiscard]] std::vector<int> getMoves(int fromIdx) const override {
        return {ChessTrainer::Utils::generateBoardIdxFromCoord(0,
                                                               this->color_
                                                                   == Color::White
                                                               ? fromIdx + 2 : fromIdx - 2)};
    }
};

#endif //CHESSTRAINER_PIECES_PAWN_HPP_
