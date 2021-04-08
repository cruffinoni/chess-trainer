
#include "IPiece.hpp"

std::string ChessTrainer::IPiece::getName() const {
    return this->name_;
}

std::string ChessTrainer::IPiece::getEmbeddedDiminutive() const {
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

ChessTrainer::IPiece::IPiece(const std::string& name,
                             char diminutive,
                             Color color) :
    name_(name), diminutive_(diminutive), color_(color) {
}

ChessTrainer::IPiece::operator bool() const {
    return this->color_ != Color::None;
}
std::string ChessTrainer::IPiece::getColorName(bool firstLetterUpperCase) const {
    switch (this->color_) {
        case Color::None: return "(none)";
        case Color::White: return firstLetterUpperCase ? "White" : "white";
        case Color::Black: return firstLetterUpperCase ? "Black" : "black";
    }
    return "invalid";
}
ChessTrainer::IPiece::Color ChessTrainer::IPiece::getColor() const {
    return this->color_;
}

char ChessTrainer::IPiece::getDiminutive() const {
    return this->diminutive_;
}

std::string ChessTrainer::IPiece::getStringDiminutive() const {
    return (std::string(1, this->getDiminutive()));
}

bool ChessTrainer::IPiece::operator==(const IPiece& a) const {
    return this->color_ == a.color_ && this->diminutive_ == a.diminutive_;
}

bool ChessTrainer::IPiece::operator!=(const IPiece& a) const {
    return this->color_ != a.color_ || this->diminutive_ != a.diminutive_;
}
std::vector<int> ChessTrainer::IPiece::getMoves(int fromIdx,
                                                const rawBoard_t& board) const {
    return {};
}

void ChessTrainer::IPiece::onMove(const ChessTrainer::Coordinates& to) {}
