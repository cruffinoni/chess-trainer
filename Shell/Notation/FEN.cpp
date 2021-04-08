
#include <algorithm>
#include <sstream>
#include "FEN.hpp"
#include "../../Utils.hpp"

bool ChessTrainer::Notation::FEN::invalidate(const std::string& reasons) {
    std::cerr << "Invalid FEN: " << reasons << std::endl;
    this->valid_ = false;
    return false;
}

bool ChessTrainer::Notation::FEN::setColor(const std::string& data) {
    if (data != "b" && data != "w") {
        return this->invalidate("invalid color from data");
    }
    this->board_.setChessColorSide(
        data == "b" ? IPiece::Color::Black : IPiece::Color::White);
    return true;
}

bool ChessTrainer::Notation::FEN::retrieveTotalMove(const std::string& data) {
    try {
        this->board_.setMinTotalMoves(std::stoi(data));
    } catch (const std::invalid_argument& e) {
        this->valid_ = false;
    } catch (const std::out_of_range& e) {
        this->valid_ = false;
    }
    if (!this->valid_)
        std::cout << "Invalid FEN: wrong number of total moves" << std::endl;
    return this->valid_;
}

ChessTrainer::Notation::FEN::FEN(const std::string& input,
                                 const IPiece::Color& forceChessBoardColorSide) {
    auto split_input = ChessTrainer::Utils::splitString(input, '/');
    if (split_input.size() != Utils::BoardSize) {
        this->invalidate(
            "invalid board size");
        return;
    }
    const auto
        & details =
        ChessTrainer::Utils::splitString(split_input[Utils::BoardSize - 1],
                                         ' ');
    if (details.size() != 6) {
        this->invalidate("missing game details");
        return;
    }
    split_input[Utils::BoardSize - 1] = details[0];
    if (!this->setColor(details[1]))
        return;
    if (!this->retrieveTotalMove(details[5]))
        return;
    uint8_t nb_line = 0;
    for (const auto& line: split_input) {
        uint8_t nb_idx = 0;
        for (const auto& c: line) {
            if (std::isdigit(c)) {
                nb_idx += c - '0';
                continue;
            }
            const uint8_t k = Utils::BoardSize - nb_line;
            switch (c) {
                case 'r':
                case 'R':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<Rock>(
                                              c == 'R' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                case 'k':
                case 'K':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<King>(
                                              c == 'K' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                case 'b':
                case 'B':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<Bishop>(
                                              c == 'B' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                case 'p':
                case 'P':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<Pawn>(
                                              c == 'P' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                case 'n':
                case 'N':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<Knight>(
                                              c == 'N' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                case 'q':
                case 'Q':
                    this->board_.setPiece(Coordinates{nb_idx, k},
                                          std::make_shared<Queen>(
                                              c == 'Q' ? IPiece::Color::White
                                                       : IPiece::Color::Black));
                    break;
                default:
                    this->invalidate(
                        "invalid character '" + std::string(1, c) + "'");
                    this->board_.clear();
                    return;
            }
            nb_idx++;
        }
        nb_line++;
    }
    this->fen_ = input;
    if (forceChessBoardColorSide != IPiece::Color::None)
        this->board_.setChessColorSide(forceChessBoardColorSide);
}

ChessTrainer::Notation::FEN::FEN(const Board& board,
                                 const IPiece::Color& forceChessBoardColorSide) {
    const auto& rawBoard = board.getRawBoard();
    uint8_t pass = 0;
    for (int i = Utils::TotalBoardSize - Utils::BoardSize; i >= 0;
         i -= Utils::BoardSize) {
        for (int j = 0; j < Utils::BoardSize; j++) {
            const auto idx = i + j;
            if (!rawBoard[idx]) {
                pass++;
            } else {
                if (pass != 0) {
                    this->fen_ += std::to_string(pass);
                    pass = 0;
                }
                char diminutive =
                    rawBoard[idx]->getColor() == IPiece::Color::Black
                    ? (char) std::tolower(rawBoard[idx]
                                              ->getDiminutive())
                    : (char) std::toupper(rawBoard[idx]
                                              ->getDiminutive());
                this->fen_ += diminutive;
            }
        }
        if (pass != 0) {
            this->fen_ += std::to_string(pass) + "/";
            pass = 0;
        } else if (i != 0)
            this->fen_ += "/";
    }
    if (pass != 0) {
        this->fen_ += std::to_string(pass);
        pass = 0;
    }
    this->board_ = rawBoard;
    this->board_.setMinTotalMoves(board.getTotalMoves());
    if (forceChessBoardColorSide != IPiece::Color::None)
        this->board_.setChessColorSide(forceChessBoardColorSide);
    this->fen_ += this->board_.getTurn() == IPiece::Color::White ? " w" : " b";
    // TODO: Changer les permissions de castle + dernière fois qu'une pièce a été prise (règle des 50 coups)
    this->fen_ += " KQkq - 0 " + std::to_string(this->board_.getTotalMoves());
}

ChessTrainer::Board& ChessTrainer::Notation::FEN::getBoard() {
    return this->board_;
}

bool ChessTrainer::Notation::FEN::isValid() const {
    return this->valid_;
}

std::string ChessTrainer::Notation::FEN::getFen() const {
    return this->fen_;
}

void ChessTrainer::Notation::FEN::setChessBoardSide(const IPiece::Color& color) {
    this->board_.setChessColorSide(color);
}
