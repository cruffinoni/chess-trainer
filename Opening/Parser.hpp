/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef CHESSTRAINER_OPENING_PARSER_HPP_
#define CHESSTRAINER_OPENING_PARSER_HPP_

#include <string>
#include <vector>
#include "../Pieces/Coordinates.hpp"
#include "IOpening.hpp"

namespace Opening {
    class Parser {
        public:
        Parser() = default;
        Parser(const std::string& fileName);

        void parse(const std::string& fileName);
        std::vector<Move> getMoves() const;
        std::string getName() const;
        std::string getDescription() const;
        IPiece::Color getColor() const;

        private:
        void reset();
        static std::vector<std::string> splitString(const std::string& rawInput,
                                                    char delim);
        static std::string retrieveLineContent(std::ifstream& stream);
        void getColorFromName();

        std::vector<Move> moves_;
        std::string name_;
        std::string description_;
        IPiece::Color color_;
    };
}

#endif //CHESSTRAINER_OPENING_PARSER_HPP_
