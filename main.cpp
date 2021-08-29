//#include <iostream>
//#include <chrono>
//#include <thread>
#include "Shell//Shell.hpp"
#include "Shell/Notation/FEN.hpp"
#include "Shell/Notation/PGN.hpp"
//#include "Opening/Parser.hpp"
//#include "Opening/Database.hpp"
#include "Leaner/LichessLearner.hpp"
#include "Logger.hpp"

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
    //ChessTrainer::Notation::PGN pgn("[Event \"?\"]\n"
    //                                "[Site \"?\"]\n"
    //                                "[Date \"????.??.??\"]\n"
    //                                "[Round \"?\"]\n"
    //                                "[White \"?\"]\n"
    //                                "[Black \"?\"]\n"
    //                                "[Result \"*\"]\n"
    //                                "\n"
    //                                "1. e4 c6 2. Nf3 d5 3. exd5 cxd5 4. d4 Nc6 5. Nc3 e6 6. Be2 Bd6 7. O-O Nf6 8. Bg5 O-O 9. Qd2 Be7 10. Rfe1 Qc7 11. Bf4 Qd7 12. Bb5 a6 13. Ba4 b5 14. Bb3 Qa7 15. Nh4 Qd7 16. Bh6 gxh6 17. Qxh6 Ne4 18. Nxe4 dxe4 19. Rxe4 f5 20. Rxe6 Kh8 21. Nxf5 Rxf5 22. Rae1 Bf8 23. Qh3 Rg5 24. Re1e4 Qg7 25. g3 Bxe6 26. Bxe6 Re8 27. d5 Ne5 28. f4 Nf3+ 29. Kh1 Rg6 30. f5 Rg5 31. Kg2 Nd4 32. c3 Nxe6 33. dxe6 Bd6 34. g4 Qf6 35. Qd3 Bb8 36. Qd7 Qh6 37. e7 Qxh2+ 38. Kf3 Qg3+ 39. Ke2 Qg2+ 40. Kd1 Qxe4 41. Qxe8+ Rg8 42. Qf7 Qxg4+ 43. Kc2 Qg2+ 44. Kb3 a5 45. e8=Q a4+ 46. Ka3 Bd6+ 47. b4 axb3+ 48. Kxb3 Rxe8 49. Qxe8+ Kg7 50. Qd7+ Kh6 51. Qxd6+ Kg5 52. f6 Qf3 53. Qe5+ Kg6 54. Qxb5 Qxf6 55. a4 Qe6+ 56. Ka3 Qd6+ 57. Qb4 Qd3 58. a5 h5 59. Qb6+ Kg5 60. Qc5+ Kg4 61. Kb4 Qb1+ 62. Kc4 Qa2+ 63. Kd3 Qb1+ 64. Kc4 Qa2+ 65. Kd4 Qd2+ 66. Kc4 Qa2+ 67. Kb5 Qb3+ 68. Qb4+ Qxb4+ 69. Kxb4 h4 70. a6 h3 71. a7 h2 72. a8=Q h1=B 73. Qxh1 Kf4 74. c4 Kg3 75. Qe1+ Kf3 76. Qd2 Ke4 77. Qc3 Kf4 78. Qd3 Ke5 79. c5 Ke6 80. c6 Ke5 81. c7 Ke6 82. Qd4 Ke7 83. c8=Q Kf7 84. Qd6 Kg7 85. Qcc7+ Kg8 86. Qdd8# 1-0");
    //pgn.getBoard().print();


    ChessTrainer::LichessLearner l("./cut_lichess_elite_2020-08.pgn");
    l.learn();
    //displayGamesByECO(l, "a");

    return 0;
}


/*
Lire toutes les games
Les enregistrer
Les ouvertures communes sont des ouvertures valides

 Pour une ajouter une ouverture, ça reprends ce principe
 Si elle inconnue et qu'elle souhaite être enregistré, proposer de l'enregistrer

 */
