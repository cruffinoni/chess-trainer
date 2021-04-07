/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <sstream>
#include <fstream>
#include <algorithm>
#include <array>
#include "Parser.hpp"

Opening::Parser::Parser(const std::string& fileName) {
    this->parse(fileName);
}

void Opening::Parser::reset() {
    this->moves_.clear();
    this->name_.clear();
    this->description_.clear();
}

void Opening::Parser::parse(const std::string& fileName) {
    this->reset();
    std::ifstream fs(fileName, std::ifstream::in);
    if (!fs.is_open())
        throw std::invalid_argument("file" + fileName + " does not exists");
    this->name_ = retrieveLineContent(fs);
    std::transform(this->name_.begin(), this->name_.end(), this->name_.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    getColorFromName();
    this->description_ = retrieveLineContent(fs);
    const auto& moves = retrieveLineContent(fs);
    for (const auto& m : splitString(moves, ';')) {
        const auto& p = splitString(m, ',');
        if (p.size() != 2)
            throw std::invalid_argument(
                "malformed file: invalid move '" + m + "'");
        this->moves_.emplace_back(Move{p[0], p[1]});
    }
}

std::string Opening::Parser::retrieveLineContent(std::ifstream& stream) {
    std::string line;
    std::getline(stream, line, ']');
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    if (line.front() != '[')
        throw std::invalid_argument("malformed file: missing '['");
    line.erase(line.begin(), line.begin() + 1);
    return line;
}

std::vector<std::string> Opening::Parser::splitString(const std::string& rawInput,
                                                      char delim) {
    std::string buff;
    std::stringstream ss(rawInput);
    std::vector<std::string> tokens;
    while (std::getline(ss, buff, delim))
        tokens.push_back(buff);
    return tokens;
}

std::string Opening::Parser::getName() const {
    return this->name_;
}

std::vector<Move> Opening::Parser::getMoves() const {
    return this->moves_;
}
std::string Opening::Parser::getDescription() const {
    return this->description_;
}

void Opening::Parser::getColorFromName() {
    const auto idx = this->name_.find('|');
    if (idx == std::string::npos) {
        this->color_ = IPiece::Color::White;
        return;
    }
    auto strColor = this->name_.substr(idx + 1);
    std::transform(strColor.begin(), strColor.end(), strColor.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    this->name_.erase(idx);
    if (strColor == "white")
        this->color_ = IPiece::Color::White;
    else if (strColor == "black")
        this->color_ = IPiece::Color::Black;
    else {
        std::cerr << "Invalid color: '" << strColor
                  << "'. it might be non-volunteer" << std::endl;
        this->color_ = IPiece::Color::White;
    }
}
IPiece::Color Opening::Parser::getColor() const {
    return this->color_;
}
