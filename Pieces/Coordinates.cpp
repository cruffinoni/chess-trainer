
#include <stdexcept>
#include "../Utils.hpp"
#include "Coordinates.hpp"

void ChessTrainer::Coordinates::validateCoordinates() const {
    if (this->coord_.x > Utils::BoardSize
        || this->coord_.y > Utils::BoardSize)
        throw std::out_of_range(std::string(
            "invalid coordinates: out of range [" + std::to_string(this->coord_.x) + ","
                + std::to_string(this->coord_.y) + "]"));
}

ChessTrainer::Coordinates::Coordinates(uint8_t x, uint8_t y) : coord_(x, y) {
    this->validateCoordinates();
}

ChessTrainer::Coordinates::Coordinates(const ChessTrainer::Coordinates::Vector2D& vec)
    : coord_(vec) {
    this->validateCoordinates();
}

ChessTrainer::Coordinates::Coordinates() : coord_(0, 0) {}

ChessTrainer::Coordinates::Coordinates(const std::string& pos) : coord_(0, 0) {
    if (pos.length() != 2)
        throw std::out_of_range("invalid coordinates: notation must be only 2 chars");
    if (pos[0] < 'a' || pos[0] > 'h')
        throw std::out_of_range("invalid coordinates: first coordinate must be between a & h: " + pos);
    if (pos[1] < '1' || pos[1] > '8')
        throw std::out_of_range("invalid coordinates: second letter must be between 1 & 8");
    this->coord_ =
        ChessTrainer::Coordinates::Vector2D(pos[0] - 'a', pos[1] - '0');
}

ChessTrainer::Coordinates::Coordinates(int boardIdx) : coord_(boardIdx % 8,
                                                              boardIdx / 8
                                                                  + 1) {
    this->validateCoordinates();
}

uint8_t ChessTrainer::Coordinates::getX() const {
    return this->coord_.x;
}

uint8_t ChessTrainer::Coordinates::getY() const {
    return this->coord_.y;
}

std::string ChessTrainer::Coordinates::toStringNotation() const {
    return std::string(1, (char) (this->coord_.x + 'a'))
        + std::string(1, (char) (this->coord_.y + '0'));
}

bool ChessTrainer::Coordinates::operator==(const Coordinates& a) const {
    return this->coord_.x == a.coord_.x && this->coord_.y == a.coord_.y;
}

bool ChessTrainer::Coordinates::operator==(int idx) const {
    return ChessTrainer::Utils::generateBoardIdxFromCoord(this->getX(),
                                                          this->getY()) == idx;
}
uint8_t ChessTrainer::Coordinates::toBoardIndex() const {
    return Utils::generateBoardIdxFromCoord(this->coord_.x, this->coord_.y);
}
