//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
#include "Shell/Notation/PGN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"

int main() {
    //ChessTrainer::Shell s;
    //s.run();
    ChessTrainer::Notation::PGN pgn("[Event \"Super event\"]\n"
                                  "[Site \"France\"]\n"
                                  "[Date \"2021.04.07\"]\n"
                                  "[Round \"2\"]\n"
                                  "[White \"White user\"]\n"
                                  "[Black \"Black user\"]\n"
                                  "[Result \"*\"]\n"
                                  "[WhiteElo \"999\"]\n"
                                  "[BlackElo \"998\"]\n"
                                  "[TimeControl \"5 + 1\"]\n"
                                  "[Termination \"\"]\n"
                                  "\n"
                                  "1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Bc5 5. Be3 Qf6 6. c3 *");

    return 0;
}
