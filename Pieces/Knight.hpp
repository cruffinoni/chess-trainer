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
};

#endif //CHESSTRAINER_PIECES_KNIGHT_HPP_
