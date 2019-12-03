#ifndef HELPER_H
#define HELPER_H

#include<list>
#include"Position.hpp"


struct Vector{
  double column;
  double row;
};

enum Colour{WHITE = -1, BLACK = 1};

const int SIZEOFBOARD = 8;


const int SUCCESS = 0;
const int NO_PIECE_IN_SQUARE = 1;
const int INCORRECT_PIECE_COLOUR = 2;
const int INVALID_INPUT_POSITION = 3;
const int TAKING_OWN_PIECE = 4;
const int PIECE_IN_THE_WAY = 5;
const int INVALID_MOVE = 6;
const int MOVE_INTO_CHECK = 7;
const int STALEMATE = 8;
const int CHECKMATE = 9;


const std::list<Position> WHITE_START_POS_ROOK = {{0,0}, {7,0}};
const std::list<Position> WHITE_START_POS_KNIGHT = {{1,0}, {6,0}};
const std::list<Position> WHITE_START_POS_BISHOP = {{1,0}, {6,0}};
const std::list<Position> WHITE_START_POS_KING = {{1,0}, {6,0}};
const std::list<Position> WHITE_START_POS_QUEEN = {{1,0}, {6,0}};
const std::list<Position> WHITE_START_POS_PAWN = {{0,1}, {1,1}, {2,1}, {3,1},
                                                  {4,1}, {5,1}, {6,1}, {7,1}};



#endif
