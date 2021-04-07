/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_KING_HPP_
#define CHESSTRAINER_PIECES_KING_HPP_

#include "IPiece.hpp"

class King : public IPiece {
    public:
    explicit King(const Color& color) : IPiece("King",
                                               'K',
                                               color) {};
    [[nodiscard]] std::vector<int> getMoves(int fromIdx) const override {
        return {
            ChessTrainer::Utils::generateBoardIdxFromCoord(-1, 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(0, 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(1, 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(-1, 0),
            ChessTrainer::Utils::generateBoardIdxFromCoord(1, 0),
            ChessTrainer::Utils::generateBoardIdxFromCoord(-1, -1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(0, -1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(1, -1)
        };
    }
};

#endif //CHESSTRAINER_PIECES_KING_HPP_
