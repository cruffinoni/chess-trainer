/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER__SHELL_HPP_
#define CHESSTRAINER__SHELL_HPP_

#include <list>
#include <string>
#include <utility>
#include "../Opening/Database.hpp"
#include "ICommand.hpp"
#include "Commands/Opening/Opening.hpp"
#include "Commands/Notation/FEN.hpp"

class Shell {
    public:
    Shell();
    void run();

    private:
    static void exit();

    std::list<std::shared_ptr<Command::ICommand>> commands_ = {
        std::make_shared<Command::Help>(),

        std::make_shared<Command::Opening>(),
        std::make_shared<Command::FEN>()
    };
    Command::Help* const helper_;
};

#endif //CHESSTRAINER__SHELL_HPP_
