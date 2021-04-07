//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"

int main() {
    //Shell s;
    //s.run();
    //Board b(IPiece::Color::White);
    //ChessTrainer::Notation::FEN b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    //ChessTrainer::Notation::FEN r(b.getBoard());
    //r.getBoard().print();
    ChessTrainer::Notation::FEN c("1k6/4R3/1B5p/8/p7/6P1/PP6/3R2K1 w - - 0 42");
    ChessTrainer::Notation::FEN f(c.getBoard());
    f.getBoard().print();
    std::cout << f.getFen() << std::endl;
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
    return 0;
}
