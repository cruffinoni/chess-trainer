/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_LEANER_LICHESSLEARNER_HPP_
#define CHESSTRAINER_LEANER_LICHESSLEARNER_HPP_

#include <string>
#include <fstream>
#include "../Shell/Notation/PGN.hpp"

namespace ChessTrainer {
    class LichessLearner {
        public:
        LichessLearner(const std::string& file);
        std::vector<Notation::PGN> getGames() const;

        std::vector<Notation::PGN> findGamesByECO(const std::string& pgn) const;
        uint32_t countOpening(const std::string& ECO_Opening) const;

        private:
        void learn();

        std::ifstream file_;
        bool isValid_;
        std::vector<Notation::PGN> games_;
    };
}

#endif //CHESSTRAINER_LEANER_LICHESSLEARNER_HPP_
