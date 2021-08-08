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

        void learn();
        std::vector<Notation::PGN> findGamesByECO(const std::string& ECO) const;

        private:
        std::ifstream file_;
        bool isValid_;
        std::vector<Notation::PGN> games_;
    };
}

#endif //CHESSTRAINER_LEANER_LICHESSLEARNER_HPP_
