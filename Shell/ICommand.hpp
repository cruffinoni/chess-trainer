/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_SHELL_ICOMMAND_HPP_
#define CHESSTRAINER_SHELL_ICOMMAND_HPP_

#include <vector>
#include <string>

namespace ChessTrainer::Command {
    class ICommand {
        public:
        explicit ICommand(const std::string& name,
                          const std::string& description);
        ~ICommand() = default;

        typedef std::vector<std::string> shellArgs_t;

        virtual void run(const shellArgs_t& args) = 0;
        std::string getName() const;
        std::string getDescription() const;

        private:
        std::string name_;
        std::string description_;
    };
}

#endif //CHESSTRAINER_SHELL_ICOMMAND_HPP_
