//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
#include "Shell/Notation/PGN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"
#include "Leaner/LichessLearner.hpp"


void displayGamesByECO(const ChessTrainer::LichessLearner &l, const std::string& eco) {
    std::cout << "===== Displaying games '" << eco << "' =====" << std::endl;
    const auto& games = l.findGamesByECO(eco);
    //printf("games: %zu\n", games.size());
    //for (const auto &item : games) {
    //    item.getBoard().print();
    //}
    std::cout << "===== END =====" << std::endl;
}

int main() {
    //ChessTrainer::Shell s;
    //s.run();
    //ChessTrainer::Notation::PGN pgn("[Event \"Rated Blitz tournament https://lichess.org/tournament/Y9v9LrwW\"]\n"
    //                                "[LichessURL \"https://lichess.org/Mk0P52uU\"]\n"
    //                                "[Date \"2020.08.01\"]\n"
    //                                "[Round \"-\"]\n"
    //                                "[White \"Pinichess\"]\n"
    //                                "[Black \"user_silva2002\"]\n"
    //                                "[Result \"0-1\"]\n"
    //                                "[WhiteElo \"2348\"]\n"
    //                                "[BlackElo \"2440\"]\n"
    //                                "[ECO \"B77\"]\n"
    //                                "[Opening \"Sicilian Defense: Dragon Variation, Yugoslav Attack, Main Line\"]\n"
    //                                "[TimeControl \"180+2\"]\n"
    //                                "[UTCDate \"2020.08.01\"]\n"
    //                                "[UTCTime \"00:00:16\"]\n"
    //                                "[Termination \"Normal\"]\n"
    //                                "[WhiteRatingDiff \"-5\"]\n"
    //                                "[BlackRatingDiff \"+5\"]\n"
    //                                "\n"
    //                                "1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 g6 6. Be3 Bg7 7. Bc4 O-O\n"
    //                                "8. f3 Nc6 9. Qd2 a6 10. Bb3 Nxd4 11. Bxd4 b5 12. a4 b4 13. Nd5 Nxd5 14.\n"
    //                                "Bxd5 Rb8 15. a5 e6 16. Bb3 d5 17. Bxg7 Kxg7 18. exd5 exd5 19. Qd4+ Kg8 20.\n"
    //                                "O-O Be6 21. Rfd1 Qc7 22. Kh1 Rb5 23. Ra4 Qe7 24. Re1 Qd6 25. Re5 Rc8 26. h3\n"
    //                                "Rcc5 27. f4 Rxa5 28. Qxb4 Rab5 29. Qd4 a5 30. Ra3 Rb4 31. Qd2 Qd8 32. Qf2\n"
    //                                "Rc8 33. f5 Qf6 34. Qe1 Rf4 35. Bxd5 Bxd5 36. Rxd5 Rxc2 37. Raxa5 Qg5 38.\n"
    //                                "Ra8+ Kg7 39. Rd2 Rxd2 40. Qxd2 Rf1+ 0-1\n"
    //                                "");
    //pgn.getBoard().print();


    ChessTrainer::LichessLearner l("./test.pgn");
    l.learn();
    displayGamesByECO(l, "C44");
    return 0;
}


/*
Lire toutes les games
Les enregistrer
Les ouvertures communes sont des ouvertures valides

 Pour une ajouter une ouverture, ça reprends ce principe
 Si elle inconnue et qu'elle souhaite être enregistré, proposer de l'enregistrer

 */
