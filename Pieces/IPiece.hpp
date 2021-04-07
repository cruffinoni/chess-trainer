/*
** EPITECH PROJECT, 2021
** ChessTrainer
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_CHESS_TRAINER_APIECE
#define SRC_CHESS_TRAINER_APIECE

#include <string>
#include <vector>
#include "Coordinates.hpp"

class IPiece {
    public:
    enum class Color : uint8_t {
        None,
        White,
        Black
    };
    virtual ~IPiece() = default;
    IPiece() = default;
    IPiece(const std::string& name, char diminutive, Color color);
    std::string getName() const;
    std::string getEmbeddedDiminutive() const;
    char getDiminutive() const;
    std::string getStringDiminutive() const;
    explicit operator bool() const;
    Color getColor() const;
    std::string getColorName(bool firstLetterUpperCase = false) const;
    virtual std::vector<int> getMoves() const;
    static int generateMoveFromCoord(int x, int y);

    protected:
    Color color_ = Color::None;
    std::string name_ = "Empty";
    char diminutive_ = '.';
};

#endif
