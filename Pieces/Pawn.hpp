/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_PIECES_PAWN_HPP_
#define CHESSTRAINER_PIECES_PAWN_HPP_

#include "IPiece.hpp"

namespace ChessTrainer {
    class Pawn : public IPiece {
        public:
        explicit Pawn(const Color& color) : IPiece("Pawn",
                                                   'P',
                                                   color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board) const override {
            return {ChessTrainer::Utils::generateBoardIdxFromCoord(0,
                                                                   this->color_
                                                                       == Color::White
                                                                   ? fromIdx + (this->moved_ ? 1 : 2)
                                                                   :
                                                                   fromIdx
                                                                       - (this->moved_ ? 1 : 2))};
        }
        void onMove(const Coordinates&) override {
            this->moved_ = true;
        }

        private:
        bool moved_ = false;
    };
}

#endif //CHESSTRAINER_PIECES_PAWN_HPP_
