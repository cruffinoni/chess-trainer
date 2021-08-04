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
                                                const rawBoard_t& board,
                                                const helperPieceData& lastMove) const override {
            const Coordinates c{fromIdx};
            const bool isWhite = this->color_ == IPiece::Color::White;
            std::vector<int> vec;
            int oneCase = isWhite ? fromIdx + ChessTrainer::Utils::BoardSize : fromIdx - ChessTrainer::Utils::BoardSize;

            if (oneCase > 0 && oneCase <= ChessTrainer::Utils::TotalBoardSize
                && !*board[oneCase])
                vec.emplace_back(oneCase);
            if (isWhite) {
                if (c.getY() == 2)
                    vec.emplace_back(Coordinates{c.getX(),
                                                 static_cast<uint8_t>(c.getY()
                                                     + 2u)}.toBoardIndex());
            } else {
                if (c.getY() == 7)
                    vec.emplace_back(Coordinates{c.getX(),
                                                 static_cast<uint8_t>(c.getY()
                                                     - 2u)}.toBoardIndex());
            }
            const std::array<int, 2> takes = {
                oneCase - 1,
                oneCase + 1
            };
            std::for_each(takes.begin(), takes.end(), [&](const int idx) {
                if (idx > 0 && idx <= ChessTrainer::Utils::TotalBoardSize && *board[idx])
                    vec.emplace_back(idx);
            });

            // En passant
            if (lastMove.piece == nullptr || !lastMove.allowEnPassant)
                return vec;
            std::array<std::array<int, 2>, 2> enPassantSides = {
                {{oneCase - 1, fromIdx - 1},
                 {oneCase + 1, fromIdx + 1}},
            };
            std::for_each(enPassantSides.begin(), enPassantSides.end(), [&](const std::array<int, 2> indexs) {
                if (indexs[0] > 0 && indexs[0] <= ChessTrainer::Utils::TotalBoardSize && !*board[indexs[0]]
                    && (lastMove.piece->getDiminutive() == 'P' && (indexs[1]) == lastMove.coordinates.toBoardIndex()))
                    vec.emplace_back(indexs[0]);
            });
            return vec;
        }

        static bool isTakeEnPassant(int fromIdx, int toIdx) {
            const int resultIdx = abs(fromIdx - toIdx);
            //printf("from %i to %i = %i\n", fromIdx, toIdx, resultIdx);
            return resultIdx == 7 || resultIdx == 9;
        }

        static bool isPawn(const IPiece& piece) {
            return piece.getDiminutive() == 'P';
        }
    };
}

#endif //CHESSTRAINER_PIECES_PAWN_HPP_
