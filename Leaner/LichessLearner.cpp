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
    size_t count = 0;
    bool isTag = false;
    while (std::getline(this->file_, line)) {
        //std::cout << "line : '" << line << "'" << std::endl;
        if (line.empty())
            isTag = false;
        else if (line[0] == '[') {
            if (!isTag && !pgn.empty()) {
                //std::cout << "end of game?\n" << pgn << std::endl;
                try {
                    this->games_.emplace_back(pgn);
                } catch (const std::out_of_range &e) {
                    //printf("out_of_range: '%s'\n", e.what());
                } catch (const Notation::PGN::Error& e) {
                    //printf("pgn err: '%s'\n", e.what());
                }
                //try {
                //    printf("game added\n");
                //    this->games_.emplace_back(pgn);
                //} catch (const Notation::PGN::Error& e) {
                //    std::cerr << "invalid game: " << e.toString() << std::endl;
                //}
                pgn.clear();
                if (++count % 50 == 0)
                    std::cout << "Number of games registered: " << count << std::endl;
                if (count >= 10000)
                    return;
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
                    this->games_.emplace_back(pgn);
                } catch (const std::out_of_range &e) {
                    //printf("out_of_range: '%s'\n", e.what());
                } catch (const Notation::PGN::Error& e) {
                    //printf("pgn err: '%s'\n", e.what());
                }
        //try {
        //    //printf("game added\n");
        //    this->games_.emplace_back(pgn);
        //} catch (const Notation::PGN::Error& e) {
        //    std::cerr << "invalid game: " << e.toString() << std::endl;
        //}
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
    //std::cout << "games: " << this->games_.size() << std::endl;
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
        std::cout << std::boolalpha << "found ? "
                  << static_cast<bool>(gameECO == tags.end()) << std::endl;
        if (gameECO == tags.end())
            continue;
        v.emplace_back(g);
        std::cout << "game added" << std::endl;
    }
    std::cout << "vector is not empty" << std::endl;
    return v;
}

std::vector<ChessTrainer::Notation::PGN> ChessTrainer::LichessLearner::getGames() const {
    return this->games_;
}


