/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_BISHOP_HPP_
#define CHESSTRAINER_PIECES_BISHOP_HPP_

#include "IPiece.hpp"

class Bishop : public IPiece {
    public:
    explicit Bishop(const Color& color) : IPiece("Bishop",
                                                 'B',
                                                 color) {};
};

#endif //CHESSTRAINER_PIECES_BISHOP_HPP_
