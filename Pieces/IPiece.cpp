/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "IPiece.hpp"

std::string IPiece::getName() const {
    return this->name_;
}

std::string IPiece::getEmbeddedDiminutive() const {
    switch (this->color_) {
        case Color::None: return (std::string(1, this->diminutive_));
        case Color::White:
            return std::string(
                "\033[1;47;30m" + std::string(1, this->diminutive_)
                    + "\033[0m");
        case Color::Black:
            return std::string(
                "\033[1;37;40m" + std::string(1, this->diminutive_)
                    + "\033[0m");
    }
    return std::string("(invalid)");
}

IPiece::IPiece(const std::string& name, char diminutive, Color color) :
    name_(name), diminutive_(diminutive), color_(color) {
}

IPiece::operator bool() const {
    return this->color_ != Color::None;
}
std::string IPiece::getColorName(bool firstLetterUpperCase) const {
    switch (this->color_) {
        case Color::None: return "(none)";
        case Color::White: return firstLetterUpperCase ? "White" : "white";
        case Color::Black: return firstLetterUpperCase ? "Black" : "black";
    }
    return "invalid";
}
IPiece::Color IPiece::getColor() const {
    return this->color_;
}

char IPiece::getDiminutive() const {
    return this->diminutive_;
}

std::string IPiece::getStringDiminutive() const {
    return (std::string(1, this->getDiminutive()));
}

bool IPiece::operator==(const IPiece& a) const {
    return this->color_ == a.color_ && this->diminutive_ == a.diminutive_;
}

bool IPiece::operator!=(const IPiece& a) const {
    return !(a == *this);
}
std::vector<int> IPiece::getMoves(int fromIdx) const {
    return {};
}
