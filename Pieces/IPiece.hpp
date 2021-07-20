
#ifndef SRC_CHESS_TRAINER_APIECE
#define SRC_CHESS_TRAINER_APIECE

#include <string>
#include <vector>
#include <memory>
#include "../Utils.hpp"
#include "Coordinates.hpp"

namespace ChessTrainer {
    class IPiece {
        public:
        enum Color : uint8_t {
            None,
            White,
            Black
        };
        friend std::ostream& operator<<(std::ostream& input, const Color& c) {
            switch (c) {
                case None:
                    input << "none";
                    break;
                case White:
                    input << "white";
                    break;
                case Black:
                    input << "black";
                    break;
            }
            return input;
        }


        using shared_ptr = std::shared_ptr<IPiece>;
        typedef std::array<shared_ptr,
                           ChessTrainer::Utils::TotalBoardSize> rawBoard_t;

        struct helperPieceData {
            IPiece::shared_ptr piece;
            Coordinates coordinates;
            char priorLine;
            bool allowEnPassant;
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

        [[nodiscard]] virtual std::vector<int> getMoves(int fromIdx,
                                                        const rawBoard_t& board,
                                                        const helperPieceData& lastMove) const;

        bool operator==(const IPiece& a) const;
        bool operator!=(const IPiece& a) const;
        friend std::ostream& operator<<(std::ostream& output, const IPiece& p) {
            output << p.getColorName(true) << " " << p.getName();
            return output;
        }

        protected:
        Color color_ = Color::None;
        std::string name_ = "Empty";
        char diminutive_ = '.';
    };
}

#endif
