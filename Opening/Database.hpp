/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_DATABASE_HPP_
#define CHESSTRAINER_DATABASE_HPP_

#include <list>
#include "IOpening.hpp"

namespace ChessTrainer {
    class Database {
        public:
        Database();
        ~Database() = default;
        Database(const Database& obj);

        IOpening findByName(std::string input);
        static IVariation findVariationByName(const IOpening& opening,
                                              const std::string& variation);
        std::list<IOpening> getList();
        //constexpr static const float satisfactionRate = 65.0f;

        private:
        void iterateFolder(const std::string& name, const std::string& suffix,
                           const std::function<void(const std::string& path)>& func);

        std::list<IOpening> opening_;
    };
}

#endif //CHESSTRAINER_DATABASE_HPP_
