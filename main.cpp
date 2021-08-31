//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
#include "Shell/Notation/PGN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"
#include "Learner/LichessLearner.hpp"
#include "Logger.hpp"

void displayGamesByECO(const ChessTrainer::LichessLearner &l, const std::string& eco) {
    std::cout << "===== Displaying games '" << eco << "' (total of " << l.countOpening(eco) << ") =====" << std::endl;
    const auto& games = l.findGamesByECO(eco);
    //const auto games = l.getGames();
    for (const auto& g: games) {
        if (!g.isValid()) {
            std::cerr << "invalid" << std::endl;
            return;
        }
        g.getBoard().print();
    }
    //printf("games: %zu\n", games.size());
    //for (const auto &item : games) {
    //    item.getBoard().print();
    //}
    std::cout << "===== END =====" << std::endl;
    //std::cout << "There is " << games.size() << " total games" << std::endl;
}

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    //ChessTrainer::Notation::PGN pgn("[Event \"Rated Blitz game\"]\n"
    //                                "[Site \"https://lichess.org/uswbl5na\"]\n"
    //                                "[White \"ddj\"]\n"
    //                                "[Black \"RUS2012\"]\n"
    //                                "[Result \"0-1\"]\n"
    //                                "[UTCDate \"2013.01.01\"]\n"
    //                                "[UTCTime \"06:34:30\"]\n"
    //                                "[WhiteElo \"1642\"]\n"
    //                                "[BlackElo \"1397\"]\n"
    //                                "[WhiteRatingDiff \"-41\"]\n"
    //                                "[BlackRatingDiff \"+18\"]\n"
    //                                "[ECO \"D02\"]\n"
    //                                "[Opening \"Queen's Pawn Game: Chigorin Variation\"]\n"
    //                                "[TimeControl \"240+1\"]\n"
    //                                "[Termination \"Time forfeit\"]\n"
    //                                "\n"
    //                                "1. d4 d5 2. Nf3 Nc6 3. e3 Bf5 4. Bb5 e6 5. Bd2 Ne7 6. Ne5 a6 7. Nxc6 bxc6 8. Ba4 Ng6 9. Nc3 Qd6 10. O-O Be7 11. Ne2 O-O 12. Nf4 Nxf4 13. exf4 h6 14. c3 e5 15. fxe5 Qg6 16. Qf3 f6 17. Bxc6 Rab8 18. Bxd5+ Kh8 19. b3 fxe5 20. Rae1 Bb1 21. Qg3 Qxg3 22. hxg3 Bxa2 23. Rxe5 Bf6 24. Re4 Bxb3 25. Bxb3 Rxb3 26. Ra1 Ra8 27. Re6 a5 28. Rc6 a4 29. Rxc7 Rb2 30. Bc1 Rc2 31. f4 Kg8 32. Be3 a3 33. c4 a2 34. c5 Rb2 35. Kh2 Rb1 36. Rxa2 Rxa2 37. d5 Re1 38. Rc8+ Kh7 39. Re8 Rd2 40. d6 Rdd1 0-1");
    //pgn.getBoard().print();


    ChessTrainer::LichessLearner l("./db_cut.pgn");
    displayGamesByECO(l, "C45");
    return 0;
}


/*
Lire toutes les games
Les enregistrer
Les ouvertures communes sont des ouvertures valides

 Pour une ajouter une ouverture, ça reprends ce principe
 Si elle inconnue et qu'elle souhaite être enregistré, proposer de l'enregistrer

 */
