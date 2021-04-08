/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "IVariation.hpp"

ChessTrainer::IVariation::IVariation(const std::string& name,
                                     const std::vector<Move>& moves)
    : name_(name), moves_(moves) {}

std::vector<ChessTrainer::Move> ChessTrainer::IVariation::getMoves() const {
    return this->moves_;
}

std::string ChessTrainer::IVariation::getName() const {
    return this->name_;
}
uint32_t ChessTrainer::IVariation::countMoves() const {
    return this->moves_.size();
}
