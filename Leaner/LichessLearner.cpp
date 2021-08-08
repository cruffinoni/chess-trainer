/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <iostream>
#include "LichessLearner.hpp"

// cut_lichess_elite_2020-08

ChessTrainer::LichessLearner::LichessLearner(const std::string& file) : file_(
    file) {
    if (!this->file_.is_open()) {
        this->isValid_ = false;
        return;
    }
}
void ChessTrainer::LichessLearner::learn() {
    if (!this->file_.is_open())
        throw std::logic_error("file is invalid: can't learn");
    std::string line;
    std::string pgn;
    bool isTag = false;
    while (std::getline(this->file_, line)) {
        //std::cout << "line : '" << line << "'" << std::endl;
        if (line.empty())
            isTag = false;
        else if (line[0] == '[') {
            if (!isTag && !pgn.empty()) {
                //std::cout << "end of game?\n" << pgn << std::endl;
                try {
                    printf("game added\n");
                    this->games_.emplace_back(pgn);
                } catch (const Notation::PGN::Error& e) {
                    std::cerr << "invalid game: " << e.toString() << std::endl;
                }
                pgn.clear();
            }
            //printf("set isTag to true\n");
            isTag = true;
        } else if (!std::isdigit(line[0]) && isTag)
            std::cerr << "invalid line ? " << line << std::endl;
        pgn += line + '\n';
    }
    //printf("pgn? '%s'\n", pgn.c_str());
    if (!pgn.empty()) {
        //std::cout << "last game detected:\n" << pgn << std::endl;
        try {
            //printf("game added\n");
            this->games_.emplace_back(pgn);
        } catch (const Notation::PGN::Error& e) {
            std::cerr << "invalid game: " << e.toString() << std::endl;
        }
    }

    //for (const auto& g: this->games_) {
    //    auto tags = g.getTags();
    //    auto o = std::find_if(tags.begin(), tags.end(), [](const Notation::PGN::GameTag& gt) {
    //        return gt.first == "Opening";
    //    });
    //    if (o == tags.end())
    //        throw std::logic_error("opening tag not found");
    //    std::cout << "Opening: " << o->second << std::endl;
    //    //g.getBoard().print();
    //}
    std::cout << "games: " << this->games_.size() << std::endl;
}
std::vector<ChessTrainer::Notation::PGN> ChessTrainer::LichessLearner::findGamesByECO(
    const std::string& ECO) const {
    std::cout << "before" << std::endl;
    std::vector<Notation::PGN> v;

    for (const auto& g: this->games_) {
        std::cout << "is valid ? " << g.isValid() << std::endl;
        auto tags = g.getTags();
        std::cout << "tags: " << tags.size() << std::endl;
        auto gameECO = std::find_if(tags.begin(),
                                    tags.end(),
                                    [&ECO](const Notation::PGN::GameTag& gt) {
                                        return gt.first == "ECO"
                                            && gt.second == ECO;
                                    });
        std::cout << std::boolalpha << "found ? " << static_cast<bool>(gameECO == tags.end()) << std::endl;
        if (gameECO == tags.end())
            continue;
        v.emplace_back(g);
        std::cout << "game added" << std::endl;
    }
    if (v.empty())
        return {Notation::PGN(
            "[Event \"Rated Blitz tournament https://lichess.org/tournament/q4Q26VPN\"]\n"
            "[LichessURL \"https://lichess.org/RcmtcfuP\"]\n"
            "[Date \"2020.08.01\"]\n"
            "[Round \"-\"]\n"
            "[White \"Dybamo\"]\n"
            "[Black \"ZicoenCuba\"]\n"
            "[Result \"1-0\"]\n"
            "[WhiteTitle \"GM\"]\n"
            "[WhiteElo \"2590\"]\n"
            "[BlackElo \"2498\"]\n"
            "[ECO \"B95\"]\n"
            "[Opening \"Sicilian Defense: Najdorf Variation\"]\n"
            "[TimeControl \"180+2\"]\n"
            "[UTCDate \"2020.08.01\"]\n"
            "[UTCTime \"00:00:30\"]\n"
            "[Termination \"Normal\"]\n"
            "[WhiteRatingDiff \"+5\"]\n"
            "[BlackRatingDiff \"-5\"]\n"
            "\n"
            "1. e4 c5 2. Nf3 d6 3. d4 cxd4 4. Nxd4 Nf6 5. Nc3 a6 6. Bg5 e6 7. Qe2 Nbd7\n"
            "8. f4 Qc7 9. O-O-O Be7 10. g4 b5 11. Bg2 Bb7 12. e5 dxe5 13. fxe5 Ng8 14.\n"
            "Bf4 Nc5 15. Rhf1 O-O-O 16. Bg3 Nh6 17. Kb1 Rhf8 18. h4 Ng8 19. g5 Rd7 20.\n"
            "Ndxb5 axb5 21. Nxb5 Qb6 22. Nd6+ Bxd6 23. exd6 Bxg2 24. Qxg2 Rb7 25. b3 Rd8\n"
            "26. Rf3 Rdd7 27. Rc3 Kd8 28. Bf2 Rxd6 29. Rxd6+ Qxd6 30. Bxc5 Qd1+ 31. Kb2\n"
            "Rb8 32. Rd3+ 1-0")};
    std::cout << "vector is not empty" << std::endl;
    return v;
}


