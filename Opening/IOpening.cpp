
#include <algorithm>
#include "IOpening.hpp"

ChessTrainer::IOpening::IOpening(const std::string& name,
                                 const std::vector<Move>& moves,
                                 const ChessTrainer::IPiece::Color& defaultBoardColor)
    : name_(name),
      moves_(moves),
      cleanBoard_(defaultBoardColor),
      playedOpeningBoard_(defaultBoardColor) {
    std::for_each(this->moves_.begin(), this->moves_.end(), [&](const Move& m) {
        this->playedOpeningBoard_.movePiece(m.from, m.to, true);
    });
}

void ChessTrainer::IOpening::executeMoves() {
    auto cpy = this->cleanBoard_;
    std::for_each(this->moves_.begin(), this->moves_.end(), [&](const Move& m) {
        this->cleanBoard_.movePiece(m.from, m.to, true);
    });
}

std::string ChessTrainer::IOpening::getName() const {
    return (this->name_);
}

void ChessTrainer::IOpening::show(bool stepBy) {
    auto cpy = this->cleanBoard_;
    std::for_each(this->moves_.begin(), this->moves_.end(), [&](const Move& m) {
        this->cleanBoard_.movePiece(m.from, m.to, false);
        if (stepBy || this->cleanBoard_.getTurn()
            == ChessTrainer::IPiece::Color::White) {
            this->cleanBoard_.printLastMove();
            this->cleanBoard_.print();
        }
    });
    this->cleanBoard_ = cpy;
}

void ChessTrainer::IOpening::printMoves() {
    auto cpy = this->cleanBoard_;
    std::for_each(this->moves_.begin(), this->moves_.end(), [&](const Move& m) {
        this->cleanBoard_.movePiece(m.from, m.to, true);
    });
    this->cleanBoard_.printAllMoves();
    this->cleanBoard_ = cpy;
}

void ChessTrainer::IOpening::showVariation(bool stepBy) {
    auto openingBoard = this->playedOpeningBoard_;
    for (const auto& v : this->variation_) {
        this->showVariation(v, stepBy);
    }
}

uint32_t ChessTrainer::IOpening::countMove() const {
    return this->playedOpeningBoard_.countMove();
}

uint16_t ChessTrainer::IOpening::countVariation() const {
    return this->variation_.size();
}
const std::vector<ChessTrainer::IVariation>& ChessTrainer::IOpening::getVariation() const {
    return this->variation_;
}

void ChessTrainer::IOpening::showVariation(const IVariation& variation,
                                           bool stepBy) {
    auto openingBoard = this->playedOpeningBoard_;
    std::cout << this->name_ << " : " << variation.getName() << std::endl;
    const auto& moves = variation.getMoves();
    std::for_each(moves.begin(), moves.end(), [&](const Move& m) {
        this->playedOpeningBoard_.movePiece(m.from, m.to, true);
        if (stepBy
            || this->playedOpeningBoard_.getTurn()
                == ChessTrainer::IPiece::Color::White
            || moves.back() == m) {
            this->playedOpeningBoard_.printLastMove();
            this->playedOpeningBoard_.print();
        }
    });
    this->playedOpeningBoard_ = openingBoard;
}

void ChessTrainer::IOpening::addVariation(const IVariation& variation) {
    this->variation_.emplace_back(variation);
}
