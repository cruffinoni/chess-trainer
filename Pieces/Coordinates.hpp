
#ifndef SRC_CHESSTRAINER_COORDINATES
#define SRC_CHESSTRAINER_COORDINATES

#include <cstdint>
#include <string>
#include <iostream>

namespace ChessTrainer {
    class Coordinates {
        public:
        struct Vector2D {
            Vector2D(uint8_t x, uint8_t y) : x(x), y(y) {};
            uint8_t x;
            uint8_t y;
        };
        Coordinates();
        Coordinates(int boardIdx);
        Coordinates(uint8_t x, uint8_t y);
        explicit Coordinates(const Vector2D& vec);
        explicit Coordinates(const std::string& pos);
        [[nodiscard]] uint8_t getX() const;
        [[nodiscard]] uint8_t getY() const;
        [[nodiscard]] std::string toStringNotation() const;
        [[nodiscard]] uint8_t toBoardIndex() const;
        bool operator==(const Coordinates& a) const;
        bool operator==(int idx) const;
        // Declare function definition in scope otherwise, windows won't
        // compile with the error code LNK2019
        friend bool operator==(int idx, const Coordinates& a) {
            return a == idx;
        }
        friend std::ostream& operator<<(std::ostream& output,
                                        const Coordinates& pos) {
            output << pos.toStringNotation();
            return output;
        }

        private:
        void validateCoordinates() const;
        Vector2D coord_;
    };

    class Move {
        public:
        Move(const std::string& from, const std::string& to);
        bool operator==(const Move& a) const {
            return this->from == a.from && this->to == a.to;
        }
        Coordinates from;
        Coordinates to;
    };
}

#endif
