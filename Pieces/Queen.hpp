/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_QUEEN_HPP_
#define CHESSTRAINER_PIECES_QUEEN_HPP_

#include "IPiece.hpp"

class Queen : public IPiece {
    public:
    explicit Queen(const Color& color) : IPiece("Queen",
                                                'Q',
                                                color) {};
};

#endif //CHESSTRAINER_PIECES_QUEEN_HPP_
