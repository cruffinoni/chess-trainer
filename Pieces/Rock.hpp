/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_ROCK_HPP_
#define CHESSTRAINER_PIECES_ROCK_HPP_

#include "IPiece.hpp"

class Rock : public IPiece {
    public:
    explicit Rock(const Color& color) : IPiece("Rock",
                                               'R',
                                               color) {};
};

#endif //CHESSTRAINER_PIECES_ROCK_HPP_
