/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <sstream>
#include <regex>
#include <iostream>
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

std::vector<std::string> ChessTrainer::Utils::splitStringBySpace(const std::string& rawInput) {
    const std::regex ws_re("\\s+");
    std::vector<std::string> vector;

    for (auto begin = std::sregex_token_iterator(rawInput.begin(),
                                                 rawInput.end(),
                                                 ws_re,
                                                 -1),
             end = std::sregex_token_iterator(); begin != end; ++begin) {
        vector.emplace_back(*begin);
        //std::cout << "vec: " << vector.back() << std::endl;
    }
    return vector;
}

int ChessTrainer::Utils::generateBoardIdxFromCoord(int x, int y) {
    if (x > Utils::BoardSize || y > Utils::BoardSize)
        throw std::out_of_range("x or y out of range");
    bool negative = x < 0 || y < 0;
    const int idx = abs(x) + (abs(y) - 1) * 8;
    return negative ? -idx : idx;
}
