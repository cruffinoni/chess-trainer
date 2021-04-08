/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <sstream>
#include <fstream>
#include <algorithm>
#include "Parser.hpp"

ChessTrainer::Opening::Parser::Parser(const std::string& fileName) {
    this->parse(fileName);
}

void ChessTrainer::Opening::Parser::reset() {
    this->moves_.clear();
    this->name_.clear();
    this->description_.clear();
}

void ChessTrainer::Opening::Parser::parse(const std::string& fileName) {
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
    for (const auto& m : ChessTrainer::Utils::splitString(moves, ';')) {
        const auto& p = ChessTrainer::Utils::splitString(m, ',');
        if (p.size() != 2)
            throw std::invalid_argument(
                "malformed file: invalid move '" + m + "'");
        this->moves_.emplace_back(Move{p[0], p[1]});
    }
}

std::string ChessTrainer::Opening::Parser::retrieveLineContent(std::ifstream& stream) {
    std::string line;
    std::getline(stream, line, ']');
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    if (line.front() != '[')
        throw std::invalid_argument("malformed file: missing '['");
    line.erase(line.begin(), line.begin() + 1);
    return line;
}

std::string ChessTrainer::Opening::Parser::getName() const {
    return this->name_;
}

std::vector<ChessTrainer::Move> ChessTrainer::Opening::Parser::getMoves() const {
    return this->moves_;
}
std::string ChessTrainer::Opening::Parser::getDescription() const {
    return this->description_;
}

void ChessTrainer::Opening::Parser::getColorFromName() {
    const auto idx = this->name_.find('|');
    if (idx == std::string::npos) {
        this->color_ = ChessTrainer::IPiece::Color::White;
        return;
    }
    auto strColor = this->name_.substr(idx + 1);
    std::transform(strColor.begin(), strColor.end(), strColor.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    this->name_.erase(idx);
    if (strColor == "white")
        this->color_ = ChessTrainer::IPiece::Color::White;
    else if (strColor == "black")
        this->color_ = ChessTrainer::IPiece::Color::Black;
    else {
        std::cerr << "Invalid color: '" << strColor
                  << "'. it might be non-volunteer" << std::endl;
        this->color_ = ChessTrainer::IPiece::Color::White;
    }
}

ChessTrainer::IPiece::Color ChessTrainer::Opening::Parser::getColor() const {
    return this->color_;
}
