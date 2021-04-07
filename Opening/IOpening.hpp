
#ifndef CHESSTRAINER_OPENING_IOPENING_HPP_
#define CHESSTRAINER_OPENING_IOPENING_HPP_

#include <string>
#include <vector>
#include <functional>
#include <optional>
#include "../Board.hpp"
#include "../Pieces/Coordinates.hpp"
#include "IVariation.hpp"

class IOpening {
    public:
    IOpening(const std::string& name, const std::vector<Move>& moves,
             const IPiece::Color& defaultBoardColor = IPiece::Color::White);
    void show(bool stepBy = false);
    void printMoves();
    std::string getName() const;
    void showVariation(bool stepBy = false);
    void showVariation(const IVariation& variation, bool stepBy = false);
    void addVariation(const IVariation& variation);
    uint32_t countMove() const;
    uint16_t countVariation() const;
    const std::vector<IVariation>& getVariation() const;

    private:
    void executeMoves();
    std::string name_;
    std::vector<Move> moves_;
    std::vector<IVariation> variation_;
    Board cleanBoard_;
    Board playedOpeningBoard_;
};

#endif //CHESSTRAINER_OPENING_IOPENING_HPP_
