
#ifndef CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
#define CHESSTRAINER_SHELL_NOTATION_PGN_HPP_

#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <ostream>
#include "../../Board.hpp"

namespace ChessTrainer::Notation {
    class PGN {
        public:
        class Error : public std::exception {
            public:
            enum ErrorType {
                NONE,

                // Tag parsing error
                TAG_ALREADY_OPEN,
                TAG_NOT_OPEN,
                TAG_EXTRA_CLOSING_TOKEN,
                TAG_QUOTE_UNCLOSED,
                TAG_NOT_CLOSED,
                TAG_MANDATORY_MISSING,

                GAME_RESULT_INVALID_PLACEMENT,
                GAME_RESULT_MISSING,
                COMMENTARY_MISSING_OPEN_TOKEN,
                COMMENTARY_MISSING_END_TOKEN,
                INVALID_NUMBER_OF_COORDINATES,

                UNKNOWN_PIECE,
                ILLEGAL_MOVE,
                PLAY_BEING_CHECKMATE,

                _RESERVED_PARSING_ERROR
            };
            Error(ErrorType parsingError, const std::string& argument) : _err(parsingError), _arg(argument) {
                this->generateMessage();
            }
            Error() : Error(NONE, "") {}
            Error(ErrorType parsingError) : Error(parsingError, "") {}

            friend std::ostream& operator<<(std::ostream& output,
                                            const Error& e) {
                output << e.toString();
                return output;
            }
            operator bool() const {
                return this->_err != ErrorType::NONE;
            }
            [[nodiscard]] std::string toString() const {
                return this->_message;
            }
            const char* what() const override {
                return this->_message.c_str();
            }

            private:
            void generateMessage() {
                const auto& t = this->_errorStr[this->_err].find("%arg%");
                if (t == std::string::npos)
                    this->_message = this->_errorStr[this->_err];
                else if (this->_arg.empty())
                    this->_message = "(argument is missing - you're using wrong constructor) + " + this->_errorStr[this->_err];
                else {
                    this->_message = this->_errorStr[this->_err].substr().replace(t, 5, this->_arg);
                }
            }
            ErrorType _err;
            std::string _arg;
            std::string _message;
            std::array<std::string, _RESERVED_PARSING_ERROR> _errorStr = {
                "none",
                "trying to open another tag while one is already opened",
                "tag must be open to read the content: extra quote",
                "tag not opened: extra closing ]",
                "tag content non closed, a quote is missing",
                "tag not closed",
                "required tag '%arg%' is missing",
                "endgame result should be at the end",
                "game's result is missing",
                "commentary opening token ('{') is missing",
                "commentary closing token ('}') is missing",
                "too much or too few coordinates in '%arg%'",
                "'%arg%' is an invalid piece notation, please check",
                "%arg% is an illegal move",
                "the game shouldn't continue if one of the players is in checkmate"
            };
        };
        using tag = std::pair<std::string, std::string>;

        explicit PGN(const std::string& input);
        [[nodiscard]] bool isValid() const;
        const Board getBoard() const;

        // --
        private:
        #ifdef _PGN_CAST_TO_VOID
            #error "_PGN_CAST_TO_VOID is already defined, this shouldn't happens"
        #else
            #define _PGN_CAST_TO_VOID(expr) (static_cast<void>(expr))
        #endif
        static bool updateCursor(const std::string& input,
                                 const int currentMove,
                                 size_t& startIdx,
                                 std::string& buffer);
        void getGameState(const std::string& input);

        size_t readTags(const std::string& input);
        void invalidate();
        void readMoves(const std::string& input);

        void applyMove(const std::string& move, int currentMove);
        static void removeComments(std::string &buffer);
        static void removeRecurrentMoveNumber(std::string& buffer,
                                       int move);
        using pieceData = std::pair<IPiece::shared_ptr, Coordinates>;
        pieceData getPiece(std::string& move, const IPiece::Color& color);
        void removeCheckOrMate(std::string& buffer);

        std::vector<tag> tags_;
        Error error_;
        static constexpr const char* required_tags_[] = {
            "event",
            "site",
            "date",
            "round",
            "white",
            "black",
            "result"
        };
        Board board_;
    };
}

#endif //CHESSTRAINER_SHELL_NOTATION_PGN_HPP_
