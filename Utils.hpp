

#ifndef CHESSTRAINER__UTILS_HPP_
#define CHESSTRAINER__UTILS_HPP_

#include <vector>
#include <string>
#include <functional>

namespace ChessTrainer::Utils {
    [[maybe_unused]] std::vector<std::string> splitString(const std::string& rawInput,
                                                          char delim);
    [[maybe_unused]] std::vector<std::string> splitStringBySpace(const std::string& rawInput);
    [[maybe_unused]] int generateBoardIdxFromCoord(int x, int y);
    static const constexpr uint8_t BoardSize = 8u;
    static const constexpr uint8_t TotalBoardSize = BoardSize * BoardSize;
}

#endif //CHESSTRAINER__UTILS_HPP_
