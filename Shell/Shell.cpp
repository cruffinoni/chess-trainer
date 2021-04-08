
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cassert>
#include "Shell.hpp"

ChessTrainer::Shell::Shell() : helper_(dynamic_cast<Command::Help*>(this
    ->commands_.front()
    .get())) {
    assert(this->helper_ != nullptr);
    this->helper_->generate("ChessTrainer", this->commands_);
}

void ChessTrainer::Shell::run() {
    std::string input;
    std::cout
        << "Welcome to ChessTrainer! Train your openings here. Start by typing a command or type 'help' to get a list."
        << std::endl;

    while (!std::cin.eof()) {
        input.clear();
        std::cout << "> ";
        std::getline(std::cin, input);
        std::string buff;
        std::stringstream ss(input);
        std::vector<std::string> tokens;
        while (getline(ss, buff, ' '))
            tokens.push_back(buff);
        if (tokens.empty())
            continue;
        if (tokens[0] == "exit") {
            return exit();
        }
        auto cmd =
            std::find_if(this->commands_.begin(),
                         this->commands_.end(),
                         [tokens](const std::shared_ptr<Command::ICommand>& c) {
                             return c->getName() == tokens[0];
                         });
        if (cmd == this->commands_.end()) {
            std::cout << "\033[91mInvalid command, try again\033[0m"
                      << std::endl;
        } else
            (*cmd)->run(tokens);
    }
}

void ChessTrainer::Shell::exit() {
    std::cout << "Thanks for using ChessTrainer. Good luck !" << std::endl;
}
