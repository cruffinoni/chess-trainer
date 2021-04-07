/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_QUEEN_HPP_
#define CHESSTRAINER_PIECES_QUEEN_HPP_

#include "IPiece.hpp"
#include "Bishop.hpp"
#include "Rock.hpp"

class Queen : public IPiece {
    public:
    explicit Queen(const Color& color) : IPiece("Queen",
                                                'Q',
                                                color) {};
    [[nodiscard]] std::vector<int> getMoves(int fromIdx) const override {
        std::vector<int> vector;
        //const auto& bishop_moves = Bishop(this->color_).getMoves();
        //const auto& rock_moves = Rock(this->color_).getMoves();
        //vector.reserve(bishop_moves.size() + rock_moves.size());
        //vector.insert(vector.begin(), bishop_moves.begin(), bishop_moves.end());
        //vector.insert(vector.begin(), rock_moves.begin(), rock_moves.end());
        return vector;
    }
};

#endif //CHESSTRAINER_PIECES_QUEEN_HPP_
