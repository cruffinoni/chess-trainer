
#ifndef SRC_CHESSTRAINER_MOVE
#define SRC_CHESSTRAINER_MOVE

#include <string>
#include "Coordinates.hpp"

namespace ChessTrainer {
    class Move {
        public:
        Move(const Coordinates& from, const Coordinates& to, bool take = false): from(from), to(to) {};
        Move(const std::string& from, const std::string& to, bool take = false): Move(Coordinates(from), Coordinates(to), take) {};
        bool operator==(const Move& a) const {
            return this->from == a.from && this->to == a.to;
        }
        Coordinates from;
        Coordinates to;
    };
}
#endif
