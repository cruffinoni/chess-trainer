/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_OPENING_IVARIATION_HPP_
#define CHESSTRAINER_OPENING_IVARIATION_HPP_

#include <vector>
#include <string>
#include "../Pieces/Coordinates.hpp"
#include "../Pieces/Move.hpp"

namespace ChessTrainer {
    class IVariation {
        public:
        IVariation(const std::string& name, const std::vector<Move>& moves);
        std::vector<Move> getMoves() const;
        std::string getName() const;
        uint32_t countMoves() const;

        private:
        std::string name_;
        std::vector<Move> moves_;
    };
}

#endif //CHESSTRAINER_OPENING_IVARIATION_HPP_
