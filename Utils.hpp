

#ifndef CHESSTRAINER__UTILS_HPP_
#define CHESSTRAINER__UTILS_HPP_

#include <vector>
#include <string>

namespace ChessTrainer::Utils {
    [[maybe_unused]] std::vector<std::string> splitString(const std::string& rawInput,
                                                    char delim);
    [[maybe_unused]] int generateBoardIdxFromCoord(int x, int y);
}

#endif //CHESSTRAINER__UTILS_HPP_
