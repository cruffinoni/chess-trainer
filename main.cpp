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
    //const auto& games = l.findGamesByECO(eco);
    const auto games = l.getGames();
    for (const auto& g: games) {
        if (!g.isValid())
            printf("Game invalid: %s\n", g.getError().toString().c_str());
        //else {
            //printf("game is valid\n");
            //g.getBoard().print();
        //}
    }
    //printf("games: %zu\n", games.size());
    //for (const auto &item : games) {
    //    item.getBoard().print();
    //}
    std::cout << "===== END =====" << std::endl;
    std::cout << "There is " << games.size() << " total games" << std::endl;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    //ChessTrainer::Notation::PGN pgn("[Event \"Rated Blitz game\"]\n"
    //                                "[LichessURL \"https://lichess.org/RRj72NPW\"]\n"
    //                                "[Date \"2020.08.01\"]\n"
    //                                "[Round \"-\"]\n"
    //                                "[White \"gsoppe\"]\n"
    //                                "[Black \"LiderChessAcademy\"]\n"
    //                                "[Result \"0-1\"]\n"
    //                                "[WhiteTitle \"IM\"]\n"
    //                                "[BlackTitle \"FM\"]\n"
    //                                "[WhiteElo \"2412\"]\n"
    //                                "[BlackElo \"2464\"]\n"
    //                                "[ECO \"D80\"]\n"
    //                                "[Opening \"Grünfeld Defense: Stockholm Variation\"]\n"
    //                                "[TimeControl \"180+0\"]\n"
    //                                "[UTCDate \"2020.08.01\"]\n"
    //                                "[UTCTime \"00:00:49\"]\n"
    //                                "[Termination \"Time forfeit\"]\n"
    //                                "[WhiteRatingDiff \"-5\"]\n"
    //                                "[BlackRatingDiff \"+5\"]\n"
    //                                "\n"
    //                                "1. d4 Nf6 2. c4 g6 3. Nc3 d5 4. Bg5 Ne4 5. Nxe4 dxe4 6. e3 Bg7 7. Qd2 c5 8.\n"
    //                                "d5 Qb6 9. O-O-O Nd7 10. Ne2 Ne5 11. Nc3 f5 12. Be2 Bd7 13. f3 exf3 14. gxf3\n"
    //                                "Qa5 15. f4 Nf7 16. Bh4 Nd6 17. Qc2 Rb8 18. Qb3 b5 19. cxb5 Nxb5 20. Nxb5\n"
    //                                "Bxb5 21. d6 c4 22. Bxc4 Bxc4 23. Qxc4 Bxb2+ 24. Kc2 Bg7 25. Rb1 Qd8 26. d7+\n"
    //                                "Kf8 27. Qe6 Qc7+ 28. Kd3 Qc3+ 29. Ke2 Qc2+ 30. Kf3 Qe4+ 31. Qxe4 fxe4+ 32.\n"
    //                                "Kxe4 Kf7 33. Rxb8 Rxb8 34. Rd1 Rd8 35. Kd5 Bf6 36. Bxf6 Kxf6 37. Kc6 Ke6\n"
    //                                "38. Kc7 h5 39. Kxd8 Kf7 40. Kc7 Kf6 41. d8=Q Kf5 42. Rd7 e6 43. Qe7 h4 44.\n"
    //                                "Rd6 Ke4 45. Qxe6+ Kf3 46. Qxg6 Kf2 47. Qh5 Kxe3 0-1");
    //pgn.getBoard().print();


    ChessTrainer::LichessLearner l("./lichess_db_standard_rated_2013-01.pgn");
    l.learn();
    displayGamesByECO(l, "a");
    return 0;
}


/*
Lire toutes les games
Les enregistrer
Les ouvertures communes sont des ouvertures valides

 Pour une ajouter une ouverture, ça reprends ce principe
 Si elle inconnue et qu'elle souhaite être enregistré, proposer de l'enregistrer

 */
