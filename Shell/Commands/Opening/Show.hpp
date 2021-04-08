
#ifndef CHESSTRAINER_COMMAND_SHOW_HPP_
#define CHESSTRAINER_COMMAND_SHOW_HPP_

#include <sstream>
#include <algorithm>
#include <string>
#include "../../ICommand.hpp"
#include "../../Help.hpp"
#include "../../../Opening/Database.hpp"

namespace ChessTrainer::Command {
    class Show : public ICommand {
        public:
        explicit Show(const Database& db) : ICommand("show",
                                                     "Show an opening graphically"),
                                            db_(db),
                                            helper_(
                                                "opening show [full] [OPENING] [:VARIATION]") {};
        Show() = delete;
        ~Show() = default;

        void run(const shellArgs_t& args) override {
            if (this->helper_.seekForHelp(args))
                return;
            if (args.size() < 3) {
                std::cout << "Missing argument" << std::endl;
                return this->helper_.run(args);
            }
            std::string fullInput;
            auto ite = args.begin();
            const bool stepBySet = args[2] == "full";
            std::advance(ite, stepBySet ? 3 : 2);
            for (auto& i = ite; i != args.end(); ++i) {
                if (*i == args.back())
                    fullInput += *i;
                else
                    fullInput += *i + " ";
            }

            std::vector<std::string> input;
            std::string buffer;
            std::stringstream ss(fullInput);
            while (std::getline(ss, buffer, ':'))
                input.push_back(buffer);
            try {
                auto opening = this->db_.findByName(input[0]);
                std::cout << opening.getName() << " in " << opening.countMove()
                          << " moves" << std::endl;
                if (input.size() == 2) {
                    input[1].erase(0, 1);
                    auto variation =
                        Database::findVariationByName(opening, input[1]);
                    opening.show(stepBySet);
                    opening.showVariation(variation, stepBySet);
                } else
                    opening.show(stepBySet);
            } catch (const std::out_of_range& e) {
                std::cout
                    << std::string(e.what())
                    << std::endl;
            }
        }

        private:
        Command::Help helper_;
        Database db_;
    };
}

#endif
