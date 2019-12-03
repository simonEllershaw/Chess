#include "Rook.hpp"


Rook::Rook(Colour colour): Piece(colour){
  startingPositions = {{0,0}};
  symbol = 'R';
}
