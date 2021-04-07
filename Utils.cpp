/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <sstream>
#include "Utils.hpp"

std::vector<std::string> ChessTrainer::Utils::splitString(const std::string& rawInput,
                                                          char delim) {
    std::string buff;
    std::stringstream ss(rawInput);
    std::vector<std::string> tokens;
    while (std::getline(ss, buff, delim))
        tokens.push_back(buff);
    return tokens;
}
int ChessTrainer::Utils::generateBoardIdxFromCoord(int x, int y) {
    bool negative = x < 0 || y < 0;
    const int idx = abs(x) + (abs(y) - 1) * 8;
    return negative ? -idx : idx;
}
