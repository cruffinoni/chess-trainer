/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <filesystem>
#include "Database.hpp"
#include "Parser.hpp"

IOpening Database::findByName(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    for (const auto& i : this->opening_) {
        if (i.getName().find(input) != std::string::npos)
            return i;
    }
    throw std::out_of_range("opening not found");
}
std::list<IOpening> Database::getList() {
    return this->opening_;
}

IVariation Database::findVariationByName(const IOpening& opening,
                                         const std::string& variation) {
    try {
        auto variations = opening.getVariation();
        for (auto& v : variations) {
            if (v.getName().find(variation) != std::string::npos)
                return v;
        }
    } catch (const std::out_of_range& e) {
        throw e;
    }
    throw std::out_of_range("variation not found");
}

Database::Database() {
    this->iterateFolder("./Opening", "op", [this](const std::string& path) {
        Opening::Parser p{path};
        this->opening_.emplace_back(IOpening{
            p.getName(), p.getMoves(), p.getColor()
        });
    });
    this->iterateFolder("./Opening", "va", [this](const std::string& path) {
        Opening::Parser p{path};
        const auto& opening = std::find_if(this->opening_.begin(),
                                           this->opening_.end(),
                                           [p](const IOpening& op) {
                                               return op.getName()
                                                   == p.getName();
                                           });
        if (opening == this->opening_.end()) {
            std::cerr << "variation called: " << p.getName()
                      << " is from an unknown opening" << std::endl;
        } else
            opening->addVariation(IVariation(p.getDescription(), p.getMoves()));
    });
}

void Database::iterateFolder(const std::string& name, const std::string& suffix,
                             const std::function<void(const std::string& path)>& func) {
    for (const auto& entry : std::filesystem::directory_iterator(name)) {
        const auto& filename = entry.path().filename();
        if (entry.is_directory()) {
            this->iterateFolder(entry.path().string(), suffix, func);
        } else {
            const auto
                idx = entry.path().filename().string().find("." + suffix);
            if (idx == std::string::npos)
                continue;
            func(entry.path().string());
        }
    }
}
Database::Database(const Database& obj) {
    this->opening_ = obj.opening_;
}
