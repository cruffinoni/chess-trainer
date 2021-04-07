
#ifndef CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
#define CHESSTRAINER_SHELL_NOTATION_PGN_HPP_

#include <string>
#include <vector>
#include <utility>
#include "../../Board.hpp"

namespace ChessTrainer::Notation {
    class PGN {
        public:
        using tag = std::pair<std::string, std::string>;

        explicit PGN(std::string input);
        [[nodiscard]] bool isValid() const;

        private:
        bool invalidate(const std::string& reasons);
        bool valid_ = true;

        std::vector<tag> tags_;
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
        bool readTags(std::string& input);
    };
}

#endif //CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
