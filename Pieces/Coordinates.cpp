
#include <stdexcept>
#include <iomanip>
#include "Coordinates.hpp"

Coordinates::Coordinates(uint8_t x, uint8_t y) : coord_(x, y) {}
Coordinates::Coordinates(const Coordinates::Vector2D& vec) : coord_(vec) {}
Coordinates::Coordinates() : coord_(0, 0) {}

Coordinates::Coordinates(const std::string& pos) : coord_(0, 0) {
    if (pos.length() != 2)
        throw std::out_of_range("notation must be only 2 chars");
    if (pos[0] < 'a' || pos[0] > 'h')
        throw std::out_of_range("first coordinate must be between a & h");
    if (pos[1] < '1' || pos[1] > '8')
        throw std::out_of_range("first coordinate must be between 1 & 8");
    this->coord_ = Coordinates::Vector2D(pos[0] - 'a', pos[1] - '0');
}

uint8_t Coordinates::getX() const {
    return this->coord_.x;
}

uint8_t Coordinates::getY() const {
    return this->coord_.y;
}

std::string Coordinates::toStringNotation() const {
    return std::string(1, (char) (this->coord_.x + 'a'))
        + std::string(1, (char) (this->coord_.y + '0'));
}

std::ostream& operator<<(std::ostream& output, const Coordinates& pos) {
    output << pos.toStringNotation();
    return output;
}
bool Coordinates::operator==(const Coordinates& a) const {
    return this->coord_.x == a.coord_.x && this->coord_.y == a.coord_.y;
}

Move::Move(const std::string& from, const std::string& to) : from(Coordinates(
    from)), to(Coordinates((to))) {}

//std::string Move::toString() const {
//    std::stringstream ss;
//    ss << std::setw(4) << std::right << white.toStringNotation() << " " << std::setw(4) << std::right << black.toStringNotation() << std::endl;
//    return (ss.str());
//}
