
#include <iostream>
#include "ICommand.hpp"

Command::ICommand::ICommand(const std::string& name,
                            const std::string& description)
    : name_(name), description_(description) {}

std::string Command::ICommand::getName() const {
    return this->name_;
}
std::string Command::ICommand::getDescription() const {
    return this->description_;
}
