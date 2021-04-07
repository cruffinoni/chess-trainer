

#ifndef CHESSTRAINER_SHELL_CMDS_FEN_HPP_
#define CHESSTRAINER_SHELL_CMDS_FEN_HPP_

#include <list>
#include <string>
#include <cassert>
#include "../../ICommand.hpp"
#include "../../Notation/FEN.hpp"

namespace Command {
    class FEN : public ICommand {
        public:
        FEN(): ICommand("fen", "Create a board from the FEN notation"),
         helper_("fen [FEN NOTATION]\n\tCreate a board from the FEN notation") {}

        void run(const shellArgs_t& args) override {
            if (args.size() == 1) {
                this->helper_.run(args);
                return;
            }
            if (args.size() != 7) {
                std::cerr << "Invalid FEN format: a part is missing" << std::endl;
                return;
            }
            std::string fenStr = args[1];
            for (auto i = args.begin() + 2; i != args.end(); ++i)
                fenStr += " " + *i;
            ChessTrainer::Notation::FEN fen{fenStr};
            std::cout << "Total moves in the game: " << fen.getBoard().getTotalMoves() << std::endl;
            if (fen.isValid())
                fen.getBoard().print();
        }

        private:
        Help helper_;
    };
}
#endif
