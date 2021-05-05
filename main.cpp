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
    ChessTrainer::Notation::PGN pgn("[Event \"Rated Blitz game\"]\n"
                                    "[Site \"https://lichess.org/cu6x7sfz\"]\n"
                                    "[White \"Danut68\"]\n"
                                    "[Black \"Kyklades\"]\n"
                                    "[Result \"0-1\"]\n"
                                    "[UTCDate \"2013.01.01\"]\n"
                                    "[UTCTime \"00:24:39\"]\n"
                                    "[WhiteElo \"1561\"]\n"
                                    "[BlackElo \"1604\"]\n"
                                    "[WhiteRatingDiff \"-10\"]\n"
                                    "[BlackRatingDiff \"+10\"]\n"
                                    "[ECO \"C45\"]\n"
                                    "[Opening \"Scotch Game\"]\n"
                                    "[TimeControl \"240+0\"]\n"
                                    "[Termination \"Time forfeit\"]\n"
                                    "\n"
                                    "1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Nxd4 5. Qxd4 c5 6. Qc4 Nf6 7. Bg5 h6 8. Bh4 g5 9. Bg3 Be7 10. Be5 Qb6 11. b3 O-O 12. Nc3 Qb4 13. Qxb4 cxb4 14. Nd5 Bd8 15. Bxf6 Bxf6 16. Nxf6+ Kg7 17. e5 b6 18. Bc4 Bb7 19. O-O Kg6 20. Bd3+ Kg7 21. f4 Rac8 22. fxg5 hxg5 23. Rf5 Kg6 24. Raf1 Rh8 25. Nxd7 Rc6 26. Rxf7+ Kh5 27. Nf6+ Kh6 28. Be4 Rxf6 29. Rf1xf6+ Kh5 30. Rxb7 a5 31. Rbxb6 a4 32. Bf3+ Kh4 33. g3+ Kh3 34. Rh6+ Rxh6 0-1");
                                    //"1. e4 e5 2. Nf3 Nc6 3. d4 exd4 0-1");
    pgn.getBoard().print();
    //pgn.getBoard().sh
    /*
     * Rh7
     * Raa3
     * Rhe6
     * ed5
     * e5
     */

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
    //                                 "[Link \"https://www.chess.com/game/live/11468625157\"]\n"
    //                                 "\n"
    //                                 "1. e4 Nc6 2. Nf3 Rb8 3. d4 Ra8 4. d5 Nb4 5. c3 e6 6. cxb4 g6 7. Ne5 h6 8. Qa4 f6\n"
    //                                 "9. Nxg6 e5 10. Nxh8 a6 11. Bc4 Qe7 12. O-O h5 13. Ng6 b5 14. Nxe7 c5 15. Bxb5\n"
    //                                 "Kf7 16. Nxc8 Bd6 17. Bxd7 c4 18. Nxd6+ Kf8 19. Bc6 Rb8 20. Qxa6 Re8 21. Nxe8 h4\n"
    //                                 "22. Nxf6 c3 23. Qc8+ Kf7 24. Qxg8+ Ke7 25. Qe6+ Kd8 26. Qd7# 1-0");
    //pgn1.getBoard().print();

    //ChessTrainer::Board b(ChessTrainer::IPiece::White);
    //ChessTrainer::Notation::FEN f(b);
    //ChessTrainer::Notation::FEN f("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", ChessTrainer::IPiece::Color::White);
    //printf("-> %i\n", f.getBoard().canMove(ChessTrainer::Knight(ChessTrainer::IPiece::Color::White), ChessTrainer::Coordinates("h8")));
    return 0;
}
