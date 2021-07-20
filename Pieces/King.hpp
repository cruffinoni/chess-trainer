
#ifndef CHESSTRAINER_PIECES_KING_HPP_
#define CHESSTRAINER_PIECES_KING_HPP_

#include "IPiece.hpp"

namespace ChessTrainer {
    class King : public IPiece {
        public:
        explicit King(const Color& color) : IPiece("King",
                                                   'K',
                                                   color) {
        };
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t&,
                                                const helperPieceData& lastMove) const override {
            const Coordinates coord(fromIdx);
            std::vector<std::pair<int, int>> posAvailable = {
                {coord.getX() - 1, coord.getY() + 1},
                {coord.getX() + 1, coord.getY() - 1},
                {coord.getX() + 1, coord.getY() + 1},
                {coord.getX() - 1, coord.getY() - 1},
                {coord.getX() - 1, coord.getY()},
                {coord.getX() + 1, coord.getY()},
                {coord.getX(), coord.getY() - 1},
                {coord.getX(), coord.getY() + 1},
            };
            std::vector<int> legalPosition;
            for (const auto& p : posAvailable) {
                if (p.first >= Utils::BoardSize || p.first < 0 ||
                    p.second > Utils::BoardSize || p.second < 0)
                    continue;
                try {
                    Coordinates c(p.first, p.second);
                    legalPosition.emplace_back(c.toBoardIndex());
                } catch (const std::out_of_range& e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            return legalPosition;
        };
    };
}

#endif //CHESSTRAINER_PIECES_KING_HPP_
