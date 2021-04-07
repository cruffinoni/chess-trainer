
#ifndef CHESSTRAINER_SHELL_FEN_HPP_
#define CHESSTRAINER_SHELL_FEN_HPP_

#include <vector>
#include <string>
#include "../../Board.hpp"

namespace ChessTrainer::Notation {
    class FEN {
        public:
        static constexpr const char* DefaultBoard =
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        explicit FEN(const std::string& input, const IPiece::Color& forceChessBoardColorSide = IPiece::Color::None);
        explicit FEN(const Board& board, const IPiece::Color& forceChessBoardColorSide = IPiece::Color::None);
        Board& getBoard();
        void setChessBoardSide(const IPiece::Color& color);
        bool isValid() const;
        std::string getFen() const;

        private:
        bool invalidate(const std::string& reasons);
        bool setColor(const std::string& data);
        bool retrieveTotalMove(const std::string& data);
        static std::vector<std::string> splitString(const std::string& rawInput,
                                                    char delim);
        Board board_;
        bool valid_ = true;
        std::string fen_;
    };
}

#endif //CHESSTRAINER_SHELL_FEN_HPP_
