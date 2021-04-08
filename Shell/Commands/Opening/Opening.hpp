/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_SHELL_OPENING_HPP_
#define CHESSTRAINER_SHELL_OPENING_HPP_

#include <list>
#include <string>
#include <memory>
#include <cassert>
#include "../../ICommand.hpp"
#include "Listing.hpp"
#include "Show.hpp"
#include "../../../Opening/Database.hpp"

namespace ChessTrainer::Command {
    class Opening : public ICommand {
        public:
        Opening() : ICommand("opening", "Interact with the different opening"),
                    helper_(dynamic_cast<Help*>(this->subCmd_.front().get())) {
            assert(this->helper_ != nullptr);
            this->helper_->generate(this->getName(), this->subCmd_);
        }
        void run(const shellArgs_t& args) override {
            if (args.size() == 1) {
                this->helper_->run(args);
                return;
            }
            const auto& subCmd = std::find_if(this->subCmd_.begin(),
                                              this->subCmd_.end(),
                                              [args](const std::shared_ptr<
                                                  ICommand>& sc) {
                                                  return sc->getName()
                                                      == args[1];
                                              });
            if (subCmd == this->subCmd_.end()) {
                std::cout << "Invalid sub-command" << std::endl;
                this->helper_->run(args);
                return;
            }
            subCmd->get()->run(args);
        }

        private:
        Database db_;
        std::list<std::shared_ptr<ICommand>> subCmd_ = {
            std::make_shared<Help>(),

            std::make_shared<Listing>(db_),
            std::make_shared<Show>(db_),
        };
        Help* const helper_;
    };
}

#endif //CHESSTRAINER_SHELL_OPENING_HPP_
