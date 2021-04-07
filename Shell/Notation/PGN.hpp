
#ifndef CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
#define CHESSTRAINER_SHELL_NOTATION_PGN_HPP_

#include <string>
#include "../../Board.hpp"

namespace ChessTrainer::Notation {
    class PGN {
        public:
        PGN(const std::string& input);

        private:
        Board board_;
    };
}

#endif //CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
