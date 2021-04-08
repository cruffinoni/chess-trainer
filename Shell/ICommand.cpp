
#include <iostream>
#include "ICommand.hpp"

ChessTrainer::Command::ICommand::ICommand(const std::string& name,
                                          const std::string& description)
    : name_(name), description_(description) {}

std::string ChessTrainer::Command::ICommand::getName() const {
    return this->name_;
}
std::string ChessTrainer::Command::ICommand::getDescription() const {
    return this->description_;
}
