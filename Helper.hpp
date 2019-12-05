#ifndef HELPER_H
#define HELPER_H

#include<list>
#include"Position.hpp"

enum Colour{WHITE = 1, BLACK = -1};

const int SIZEOFBOARD = 8;
const Position MOVE_NOT_STRAIGHT = {0,0};
const int LENGTH_INPUT_STRINGS = 2; //Maybe should be 3??


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
const int TAKES_KING = 10;

const std::list<Position> WHITE_START_POS_ROOK = {{0,0}, {7,0}};
const std::list<Position> WHITE_START_POS_KNIGHT = {{1,0}, {6,0}};
const std::list<Position> WHITE_START_POS_BISHOP = {{2,0}, {5,0}};
const std::list<Position> WHITE_START_POS_KING = {{4,0}};
const std::list<Position> WHITE_START_POS_QUEEN = {{3,0}};
const std::list<Position> WHITE_START_POS_PAWN = {{0,1}, {1,1}, {2,1}, {3,1},
                                                  {4,1}, {5,1}, {6,1}, {7,1}};

const char SYMBOL_ROOK = 'R';
const char SYMBOL_KNIGHT = 'H';
const char SYMBOL_BISHOP = 'B';
const char SYMBOL_KING = 'K';
const char SYMBOL_QUEEN = 'Q';
const char SYMBOL_PAWN = 'P';

Position whiteToBlackStartPos(const Position& whiteStartPosition);

#endif
