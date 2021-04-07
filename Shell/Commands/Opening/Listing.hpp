/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_SHELL_OPENING_LISTING_HPP_
#define CHESSTRAINER_SHELL_OPENING_LISTING_HPP_

#include "../../ICommand.hpp"
#include "../../Help.hpp"
#include "../../../Opening/Database.hpp"
#include "Variation.hpp"

namespace Command {
    class Listing : public ICommand {
        public:
        explicit Listing(const Database& db)
            : ICommand("list", "List all opening indexed"),
              db_(db),
              variation_(db_),
              helper_("list", this->variation_) {};
        Listing() = delete;
        ~Listing() = default;

        void run(const shellArgs_t& args) override {
            if (this->helper_.seekForHelp(args))
                return;
            if (args.size() == 3) {
                if (args[2] != this->variation_.getName())
                    return this->helper_.run(args);
                return this->variation_.run(args);
            }
            for (const auto& i: this->db_.getList()) {
                std::cout << i.getName() << ": " << i.countMove() << " moves | "
                          << i.countVariation() << " variations registered"
                          << std::endl;
            }
        }

        private:
        Database db_;
        Variation variation_;
        Command::Help helper_;
    };
}

#endif //CHESSTRAINER_SHELL_OPENING_LISTING_HPP_
