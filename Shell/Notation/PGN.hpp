
#ifndef CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
#define CHESSTRAINER_SHELL_NOTATION_PGN_HPP_

#include <string>
#include <vector>
#include <utility>
#include "../../Board.hpp"

namespace ChessTrainer::Notation {
    class PGN {
        public:
        PGN(std::string input);
        bool isValid() const;

        private:
        bool invalidate(const std::string& reasons);
        bool valid_ = true;

        std::vector<std::pair<std::string, std::string>> tags_;
        constexpr const static char* required_tags_[] = {
            "event",
            "site",
            "date",
            "round",
            "white",
            "black",
            "result"
        };
        Board board_;
        bool readTags(std::string& line);
    };
}

#endif //CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
