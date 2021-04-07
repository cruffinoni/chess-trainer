//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
#include "Shell/Notation/PGN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"

int main() {
    //Shell s;
    //s.run();
    //Board b(IPiece::Color::White);
    //ChessTrainer::Notation::FEN b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //ChessTrainer::Notation::FEN r(b.getBoard());
    //r.getBoard().print();
    //ChessTrainer::Notation::FEN c("1k6/4R3/1B5p/8/p7/6P1/PP6/3R2K1 w - - 0 42");
    //ChessTrainer::Notation::FEN f(c.getBoard());
    //f.getBoard().print();
    //std::cout << f.getFen() << std::endl;
    //ChessTrainer::Notation::FEN b("r1b1kbn1/3pN3/p4p2/1BpPp2p/QP2P3/8/PP3PPP/RNB2RK1 b - - 0 15", IPiece::Color::White);
    //b.getBoard().print();
    //b.getBoard().setChessColorSide(IPiece::Color::White);
    //b.getBoard().print();
    //ChessTrainer::Notation::FEN
    //    a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //ChessTrainer::Notation::FEN e("8/3p4/8/8/8/8/8/8 b KQkq - 0 1");
    //a.getBoard().print();
    //ChessTrainer::Notation::FEN r("r1bqkbnr/pppp1ppp/2n5/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq d3 0 3");
    //ChessTrainer::Notation::FEN g("r1bqkbnr/pppp1ppp/2n5/4p3/3PP3/5N2/PPP2PPP/RNBQKB1R w KQkq d3 0 3");

/*
[Event "F/S Return Match"]
[Site "Belgrade, Serbia JUG"]
[Date "1992.11.04"]
[Round "29"]
[White "Fischer, Robert J."]
[Black "Spassky, Boris V."]
[Result "1/2-1/2"]

1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 {This opening is called the Ruy Lopez.}
4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 d6 8. c3 O-O 9. h3 Nb8 10. d4 Nbd7
11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15. Nb1 h6 16. Bh4 c5 17. dxe5
Nxe4 18. Bxe7 Qxe7 19. exd6 Qf6 20. Nbd2 Nxd6 21. Nc4 Nxc4 22. Bxc4 Nb6
23. Ne5 Rae8 24. Bxf7+ Rxf7 25. Nxf7 Rxe1+ 26. Qxe1 Kxf7 27. Qe3 Qg5 28. Qxg5
hxg5 29. b3 Ke6 30. a3 Kd6 31. axb4 cxb4 32. Ra5 Nd5 33. f3 Bc8 34. Kf2 Bf5
35. Ra7 g6 36. Ra6+ Kc5 37. Ke1 Nf4 38. g3 Nxh3 39. Kd2 Kb5 40. Rd6 Kc5 41. Ra6
Nf2 42. g4 Bd3 43. Re6 1/2-1/2
 */

    ChessTrainer::Notation::PGN a("[Event \"F/S Return Match\"]\n"
                                  "[Site \"Belgrade, Serbia JUG\"]");
    return 0;
}
