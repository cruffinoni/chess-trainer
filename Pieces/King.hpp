
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
                                                const rawBoard_t&) const override {
            const Coordinates coord(fromIdx);
            return {
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 1,
                                                               coord.getY()
                                                                   + 1),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX(),
                                                               coord.getY()
                                                                   + 1),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 1,
                                                               coord.getY()
                                                                   + 1),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 1,
                                                               coord.getY()),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 1,
                                                               coord.getY()),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() - 1,
                                                               coord.getY()
                                                                   - 1),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX(),
                                                               coord.getY()
                                                                   - 1),
                ChessTrainer::Utils::generateBoardIdxFromCoord(coord.getX() + 1,
                                                               coord.getY() - 1)
            };
        }
    };
}

#endif //CHESSTRAINER_PIECES_KING_HPP_
