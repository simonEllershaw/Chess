#ifndef HELPER_H
#define HELPER_H

struct Position {
  int column;
  int row;
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

#endif
