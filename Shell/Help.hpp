/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_COMMAND_HELP_HPP_
#define CHESSTRAINER_COMMAND_HELP_HPP_

#include <list>
#include <memory>
#include "ICommand.hpp"

namespace Command {
    class Help : public ICommand {
        public:
        explicit Help(const std::string& message);
        explicit Help(const std::string& title, const ICommand& cmd);
        Help();

        void run(const shellArgs_t&) override;
        void generate(const std::string& title,
                      const std::list<std::shared_ptr<ICommand>>& subcommands);
        void setHelpMessage(const std::string& msg);
        bool seekForHelp(const ICommand::shellArgs_t& args);

        private:
        std::string message_;
    };
}

#endif //CHESSTRAINER_COMMAND_HELP_HPP_
