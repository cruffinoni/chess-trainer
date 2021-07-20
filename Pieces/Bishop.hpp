
#ifndef CHESSTRAINER_PIECES_BISHOP_HPP_
#define CHESSTRAINER_PIECES_BISHOP_HPP_

#include <functional>
#include "IPiece.hpp"

namespace ChessTrainer {
    class Bishop : public IPiece {
        public:
        explicit Bishop(const Color& color) : IPiece("Bishop",
                                                     'B',
                                                     color) {};
        [[nodiscard]] std::vector<int> getMoves(int fromIdx,
                                                const rawBoard_t& board,
                                                const helperPieceData& lastMove) const override {
            std::vector<int> vector;
            Coordinates pos(fromIdx);

            this->addLegalCoordinates(board, [&pos](int i) -> int {
                if (pos.getX() - i < 0 || pos.getY() - i < 0)
                    return -1;
                return ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() - i,
                    pos.getY() - i);
            }, vector);

            this->addLegalCoordinates(board, [&pos](int i) -> int {
                if (pos.getX() + i >= Utils::BoardSize
                    || pos.getY() + i > Utils::BoardSize)
                    return -1;
                return ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() + i,
                    pos.getY() + i);
            }, vector);
            this->addLegalCoordinates(board, [&pos](int i) -> int {
                if (pos.getX() - i < 0 || pos.getY() + i > Utils::BoardSize)
                    return -1;
                return ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() - i,
                    pos.getY() + i);
            }, vector);
            this->addLegalCoordinates(board, [&pos](int i) -> int {
                if (pos.getX() + i >= Utils::BoardSize || pos.getY() - i < 0)
                    return -1;
                return ChessTrainer::Utils::generateBoardIdxFromCoord(
                    pos.getX() + i,
                    pos.getY() - i);
            }, vector);
            //std::sort(vector.begin(), vector.end());
            //for (const auto& v: vector)
            //    std::cout << "v: " << v << std::endl;
            return vector;
        };
        private:
        void addLegalCoordinates(const rawBoard_t& board,
                                 const std::function<int(int)>& getCoordFunc,
                                 std::vector<int>& vector) const {
            for (int i = 1; i <= 8; ++i) {
                const int idx = getCoordFunc(i);
                if (idx < 0 || idx >= ChessTrainer::Utils::TotalBoardSize)
                    return;
                if (*board[idx]) {
                    if (board[idx]->getColor() != this->color_)
                        vector.emplace_back(idx);
                    return;
                }
                vector.emplace_back(idx);
            }
        }
    };
}

#endif //CHESSTRAINER_PIECES_BISHOP_HPP_
