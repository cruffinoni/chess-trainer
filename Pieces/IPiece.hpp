
#ifndef SRC_CHESS_TRAINER_APIECE
#define SRC_CHESS_TRAINER_APIECE

#include <string>
#include <vector>
#include "../Utils.hpp"
#include "Coordinates.hpp"

namespace ChessTrainer {
    class IPiece {
        public:
        enum class Color : uint8_t {
            None,
            White,
            Black
        };
        typedef std::array<std::shared_ptr<IPiece>,
                           ChessTrainer::Utils::TotalBoardSize> rawBoard_t;
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
                                                        const rawBoard_t& board) const;
        virtual void onMove(const Coordinates& to);

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
