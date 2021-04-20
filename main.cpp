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
    //                                "1. e4 d5 2. Qh5 e5 3. d4 c6 {[%c_arrow\n"
    //                                "e5d4;color;#c93430;opacity;0.95;from;e5;to;d4,d5e4;color;#c93430;opacity;0.95;from;d5;to;e4]}\n"
    //                                "4. Bg5 b6 5. Nd2 a6 6. O-O-O c5 *");
    //pgn.getBoard().print();
    ChessTrainer::Notation::PGN pgn1("[Event \"Live Chess\"]\n"
                                     "[Site \"Chess.com\"]\n"
                                     "[Date \"2021.04.06\"]\n"
                                     "[Round \"-\"]\n"
                                     "[White \"Dayrion\"]\n"
                                     "[Black \"Komodo1\"]\n"
                                     "[Result \"1-0\"]\n"
                                     "[CurrentPosition \"3k4/3Q4/2B2N2/3Pp3/1P2P2p/2p5/PP3PPP/RNB2RK1 b - -\"]\n"
                                     "[Timezone \"UTC\"]\n"
                                     "[ECO \"B00\"]\n"
                                     "[ECOUrl \"https://www.chess.com/openings/Nimzowitsch-Defense-Declined\"]\n"
                                     "[UTCDate \"2021.04.06\"]\n"
                                     "[UTCTime \"17:18:41\"]\n"
                                     "[WhiteElo \"440\"]\n"
                                     "[BlackElo \"205\"]\n"
                                     "[TimeControl \"180\"]\n"
                                     "[Termination \"Dayrion won by checkmate\"]\n"
                                     "[StartTime \"17:18:41\"]\n"
                                     "[EndDate \"2021.04.06\"]\n"
                                     "[EndTime \"17:20:46\"]\n"
                                     "[Link \"https://www.chess.com/game/live/11468625157\"]\n"
                                     "\n"
                                     "1. e4 Nc6 2. Nf3 Rb8 3. d4 Ra8 4. d5 Nb4 5. c3 e6 6. cxb4 g6 7. Ne5 h6 8. Qa4 f6\n"
                                     "9. Nxg6 e5 10. Nxh8 a6 11. Bc4 Qe7 12. O-O h5 13. Ng6 b5 14. Nxe7 c5 15. Bxb5\n"
                                     "Kf7 16. Nxc8 Bd6 17. Bxd7 c4 18. Nxd6+ Kf8 19. Bc6 Rb8 20. Qxa6 Re8 21. Nxe8 h4\n"
                                     "22. Nxf6 c3 23. Qc8+ Kf7 24. Qxg8+ Ke7 25. Qe6+ Kd8 26. Qd7# 1-0");
    pgn1.getBoard().print();

    //ChessTrainer::Notation::FEN f("r1bqkbnr/pppp4/5pNp/3Pp3/QP2P3/8/PP3PPP/R1B1KB1R w KQk - 0 10", ChessTrainer::IPiece::Color::White);
    //printf("-> %i\n", f.getBoard().canMove(ChessTrainer::Knight(ChessTrainer::IPiece::Color::White), ChessTrainer::Coordinates("h8")));
    return 0;
}
