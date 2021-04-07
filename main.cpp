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
    //                              "1. e4 e5 2. Nf3 Nc6 3. d4 exd4 4. Nxd4 Bc5 5. Be3 Qf6 6. c3 *");

    ChessTrainer::Notation::FEN fen("8/8/8/4R3/8/8/8/8 w - - 0 1");
    Board b(fen.getBoard());

    const auto& test_move =
        [&](const IPiece& piece, const Coordinates& coord, bool pass) {
            if (b.canMove(piece, coord) != pass)
                std::cerr << "Pass failed: should be " << std::boolalpha << pass
                          << " but is " << !pass << " instead. Coordinates: "
                          << coord << std::endl;
            else
                std::cout << "Test " << coord << " passed" << std::endl;
        };

    test_move(Rock(IPiece::Color::White), Coordinates{"f5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"g5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"h5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"d5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"a5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"b5"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"c5"}, true);

    test_move(Rock(IPiece::Color::White), Coordinates{"e4"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e3"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e2"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e1"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e6"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e7"}, true);
    test_move(Rock(IPiece::Color::White), Coordinates{"e8"}, true);

    test_move(Rock(IPiece::Color::White), Coordinates{"f4"}, false);
    test_move(Rock(IPiece::Color::White), Coordinates{"d4"}, false);
    test_move(Rock(IPiece::Color::White), Coordinates{"d6"}, false);
    test_move(Rock(IPiece::Color::White), Coordinates{"c7"}, false);
    test_move(Rock(IPiece::Color::White), Coordinates{"f6"}, false);

    //test_move(Queen(IPiece::Color::White), Coordinates{"e4"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"d5"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"d4"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"d6"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"f6"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"f5"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"e6"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"f6"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"h8"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"a1"}, true);
    //test_move(Queen(IPiece::Color::White), Coordinates{"h5"}, true);
    //
    //test_move(Queen(IPiece::Color::White), Coordinates{"g4"}, false);
    //test_move(Queen(IPiece::Color::White), Coordinates{"f3"}, false);
    //test_move(Queen(IPiece::Color::White), Coordinates{"h4"}, false);
    //test_move(Queen(IPiece::Color::White), Coordinates{"h3"}, false);
    //test_move(Queen(IPiece::Color::White), Coordinates{"a4"}, false);
    //test_move(Queen(IPiece::Color::White), Coordinates{"b4"}, false);
    //printf("The piece can move: %i\n", b.canMove(Pawn(IPiece::Color::Black), Coordinates{"e4"}));
    return 0;
}
