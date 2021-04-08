
#include <iostream>
#include <memory>
#include "Help.hpp"

ChessTrainer::Command::Help::Help(const std::string& message) : ICommand("help",
                                                                         "Show this help message"),
                                                                message_(message) {}

void ChessTrainer::Command::Help::run(const ICommand::shellArgs_t&) {
    std::cout << this->message_ << std::endl;
}

ChessTrainer::Command::Help::Help() : Help("(help message not defined)") {}

ChessTrainer::Command::Help::Help(const std::string& title, const ICommand& cmd)
    : Help() {
    std::string newMessage =
        title + " [COMMANDS]\nCOMMANDS:\n" + "\t" + cmd.getName() + ": "
            + cmd.getDescription() + "\n";
    this->message_ = newMessage;
}

void ChessTrainer::Command::Help::setHelpMessage(const std::string& msg) {
    this->message_ = msg;
}

bool ChessTrainer::Command::Help::seekForHelp(const Command::ICommand::shellArgs_t& args) {
    for (const auto& i: args) {
        if (i == "help") {
            this->run(args);
            return true;
        }
    }
    return false;
}

void ChessTrainer::Command::Help::generate(const std::string& title,
                                           const std::list<std::shared_ptr<
                                               ICommand>>& sub) {
    auto startIte = sub.begin();
    std::string newMessage = title + " [COMMANDS]\nCOMMANDS:\n";

    for (auto& c = startIte; c != sub.end(); ++c)
        newMessage +=
            "\t" + (*c)->getName() + ": " + (*c)->getDescription() + "\n";
    this->message_ = newMessage;
}
