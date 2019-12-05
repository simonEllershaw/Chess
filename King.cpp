#include "King.hpp"
#include "Helper.hpp"

King::King(Colour colour): Piece(colour, SYMBOL_KING){}

bool King::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  // King can move 1 square in any direction
  if(currentMoveVector.normalVector != MOVE_NOT_STRAIGHT &&
     currentMoveVector.magnitude == 1) {
     return true;
   }
  else return false;
}
