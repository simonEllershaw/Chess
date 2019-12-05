#include "Queen.hpp"
#include "Helper.hpp"

Queen::Queen(Colour colour): Piece(colour, SYMBOL_QUEEN){}

bool Queen::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  // All moves are valid for a queen as long as they are straight
  if(currentMoveVector.normalVector != MOVE_NOT_STRAIGHT) return true;
  else return false;
}
