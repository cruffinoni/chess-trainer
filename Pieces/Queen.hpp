
#ifndef CHESSTRAINER_PIECES_QUEEN_HPP_
#define CHESSTRAINER_PIECES_QUEEN_HPP_

#include "IPiece.hpp"
#include "Bishop.hpp"
#include "Rock.hpp"

namespace ChessTrainer {
    class Queen : public IPiece {
        public:
        explicit Queen(const Color& color) : IPiece("Queen",
                                                    'Q',
                                                    color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board,
                                                const helperPieceData& lastMove) const override {
            std::vector<int> vector;
            const auto& bishop_moves = Bishop(this->color_).getMoves(fromIdx,
                                                                     board, {});
            const auto& rock_moves = Rock(this->color_).getMoves(fromIdx,
                                                                 board, {});
            vector.reserve(bishop_moves.size() + rock_moves.size());
            vector.insert(vector.begin(),
                          bishop_moves.begin(),
                          bishop_moves.end());
            vector.insert(vector.begin(), rock_moves.begin(), rock_moves.end());
            //std::sort(vector.begin(), vector.end());
            return vector;
        }
    };
}

#endif //CHESSTRAINER_PIECES_QUEEN_HPP_
