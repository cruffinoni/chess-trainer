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
    //ChessTrainer::Notation::PGN pgn("[Event \"Super event\"]\n"
    //                              "[Site \"France\"]\n"
    //                              "[Date \"2021.04.07\"]\n"
    //                              "[Round \"2\"]\n"
    //                              "[White \"White user\"]\n"
    //                              "[Black \"Black user\"]\n"
    //                              "[Result \"*\"]\n"
    //                              "[WhiteElo \"999\"]\n"
    //                              "[BlackElo \"998\"]\n"
    //                              "[TimeControl \"5 + 1\"]\n"
    //                              "[Termination \"\"]\n"
    //                              "\n"
    //                                "1. e4 Nc6 2. h3 e5 *");
    //                                //"1. Qxg8+ e5 2. e4 e5 *");
    //pgn.getBoard().print();
    //ChessTrainer::Notation::PGN pgn1("[Event \"Live Chess\"]\n"
    //                                 "[Site \"Chess.com\"]\n"
    //                                 "[Date \"2021.04.06\"]\n"
    //                                 "[Round \"-\"]\n"
    //                                 "[White \"Dayrion\"]\n"
    //                                 "[Black \"Komodo1\"]\n"
    //                                 "[Result \"1-0\"]\n"
    //                                 "[CurrentPosition \"3k4/3Q4/2B2N2/3Pp3/1P2P2p/2p5/PP3PPP/RNB2RK1 b - -\"]\n"
    //                                 "[Timezone \"UTC\"]\n"
    //                                 "[ECO \"B00\"]\n"
    //                                 "[ECOUrl \"https://www.chess.com/openings/Nimzowitsch-Defense-Declined\"]\n"
    //                                 "[UTCDate \"2021.04.06\"]\n"
    //                                 "[UTCTime \"17:18:41\"]\n"
    //                                 "[WhiteElo \"440\"]\n"
    //                                 "[BlackElo \"205\"]\n"
    //                                 "[TimeControl \"180\"]\n"
    //                                 "[Termination \"Dayrion won by checkmate\"]\n"
    //                                 "[StartTime \"17:18:41\"]\n"
    //                                 "[EndDate \"2021.04.06\"]\n"
    //                                 "[EndTime \"17:20:46\"]\n"
    //                                 "[Link \"https://www.chess.com/game/live/11468625157\"]\n"
    //                                 "\n"
    //                                 "1. e4 Nc6 2. Nf3 Rb8 3. d4 Ra8 4. d5 Nb4 5. c3 e6 6. cxb4 g6 7. Ne5 h6 8. Qa4 f6 1-0");
    //pgn1.getBoard().print();

    ChessTrainer::Notation::FEN f("8/8/8/8/8/8/8/3B4 w - - 0 1", ChessTrainer::IPiece::Color::White);
    printf("-> %i\n", f.getBoard().canMove(ChessTrainer::Bishop(ChessTrainer::IPiece::Color::White), ChessTrainer::Coordinates("a4")));
    return 0;
}
