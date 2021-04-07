/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef CHESSTRAINER_COMMAND_VARIATION_HPP_
#define CHESSTRAINER_COMMAND_VARIATION_HPP_

#include <iostream>
#include "../../ICommand.hpp"
#include "../../../Opening/Database.hpp"

namespace Command {
    class Variation : public ICommand {
        public:
        explicit Variation(const Database& db) : ICommand("variation",
                                                          "Display all variation possible with some detailed infos"),
                                                 db_(db) {};

        void run(const shellArgs_t& args) override {
            for (const auto& i: this->db_.getList()) {
                std::cout << i.getName() << ": " << i.countMove() << " moves"
                          << std::endl;
                for (auto& v: i.getVariation()) {
                    std::cout << "\t" << v.getName() << ": " << v.countMoves()
                              << " moves" << std::endl;
                }
            }
        };

        private:
        Database db_;
    };
}

#endif
