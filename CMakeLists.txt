cmake_minimum_required(VERSION 3.17)
project(ChessTrainer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(ChessTrainer
        main.cpp
        Board.cpp
        Board.hpp
        Pieces/IPiece.hpp
        Pieces/Coordinates.hpp
        Pieces/Coordinates.cpp
        Pieces/Pawn.hpp
        Pieces/IPiece.cpp
        Pieces/Rock.hpp
        Pieces/Knight.hpp
        Pieces/Bishop.hpp
        Pieces/Queen.hpp
        Pieces/King.hpp
        Opening/IOpening.cpp
        Opening/IOpening.hpp
        Opening/IVariation.cpp
        Opening/IVariation.hpp
        Shell/Shell.cpp
        Shell/Shell.hpp
        Opening/Database.cpp
        Opening/Database.hpp
        Shell/ICommand.cpp
        Shell/ICommand.hpp
        Shell/Commands/Opening/Opening.hpp
        Shell/Commands/Opening/Listing.hpp
        Shell/Help.cpp
        Shell/Help.hpp
        Shell/Commands/Opening/Variation.hpp
        Shell/Commands/Opening/Show.hpp
        Opening/Parser.cpp
        Opening/Parser.hpp Shell/Notation/FEN.cpp Shell/Notation/FEN.hpp Shell/Commands/Notation/FEN.hpp Shell/Notation/PGN.cpp Shell/Notation/PGN.hpp Utils.cpp Utils.hpp)
