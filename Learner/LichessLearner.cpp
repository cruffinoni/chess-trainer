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
    this->learn();
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
                const Notation::PGN game(pgn);
                if (game.isValid())
                    this->games_.emplace_back(game);
                //else {
                //    std::cerr << "Game is invalid: "
                //              << game.getError().toString() << std::endl;
                //    std::cerr << "PGN: \n" << pgn << std::endl;
                //}
                pgn.clear();
                if (++count % 50 == 0)
                    std::cout << "Number of games registered: " << count
                              << std::endl;
                if (count >= 10000)
                    return;
            }
            isTag = true;
        } else if (!std::isdigit(line[0]) && isTag)
            std::cerr << "invalid line ? " << line << std::endl;
        pgn += line + '\n';
    }
    if (!pgn.empty()) {
        const Notation::PGN game(pgn);
        if (game.isValid())
            this->games_.emplace_back(game);
        //else {
        //    std::cerr << "Game is invalid: "
        //              << game.getError().toString() << std::endl;
        //    std::cerr << "PGN: \n" << pgn << std::endl;
        //}
    }
    printf("Total valid game %zu/%zu\n", this->games_.size(), count);
}

std::vector<ChessTrainer::Notation::PGN>
ChessTrainer::LichessLearner::findGamesByECO(
    const std::string& ECO) const {
    std::cout << "before" << std::endl;
    std::vector<Notation::PGN> v;

    std::for_each(this->games_.begin(),
                  this->games_.end(),
                  [&](const Notation::PGN& pgn) {
                      const std::vector<ChessTrainer::Notation::PGN::GameTag> tagList = pgn.getTags();
                      const auto opening = std::find_if(tagList.begin(),
                                                        tagList.end(),
                                                        [&](const Notation::PGN::GameTag& tag) -> bool {
                                                            return tag.first ==
                                                                "ECO";
                                                        });
                      if (opening != tagList.end() &&
                          opening->second == ECO)
                          v.emplace_back(pgn);
                  });
    return v;
}

std::vector<ChessTrainer::Notation::PGN>
ChessTrainer::LichessLearner::getGames() const {
    return this->games_;
}

uint32_t
ChessTrainer::LichessLearner::countOpening(const std::string& ECO_Opening) const {
    uint32_t count = 0;
    std::for_each(this->games_.begin(),
                  this->games_.end(),
                  [&](const Notation::PGN& item) {
                      const std::vector<ChessTrainer::Notation::PGN::GameTag> tagList = item.getTags();
                      const auto opening = std::find_if(tagList.begin(),
                                                        tagList.end(),
                                                        [&](const Notation::PGN::GameTag& tag) -> bool {
                                                            return tag.first ==
                                                                "ECO";
                                                        });
                      if (opening != tagList.end() &&
                          opening->second == ECO_Opening)
                          count++;
                  });
    return count;
}


