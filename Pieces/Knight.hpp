/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_KNIGHT_HPP_
#define CHESSTRAINER_PIECES_KNIGHT_HPP_

#include "IPiece.hpp"

class Knight : public IPiece {
    public:
    explicit Knight(const Color& color) : IPiece("Knight",
                                                 'N',
                                                 color) {};
    [[nodiscard]] std::vector<int> getMoves(int fromIdx) const override {
        const Coordinates coord(fromIdx);
        return {
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 3, coord.getY() - 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 3, coord.getY() + 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 1, coord.getY() + 3),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 1, coord.getY() + 3),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 3, coord.getY() + 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 3, coord.getY() - 1),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 1, coord.getY() - 3),
            ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 1, coord.getY() - 3),
        };
    }
};

#endif //CHESSTRAINER_PIECES_KNIGHT_HPP_
