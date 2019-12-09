#include "King.hpp"
#include "Helper.hpp"

King::King(Colour colour): Piece(colour, SYMBOL_KING, "King"){}

bool King::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  // King can move 1 square in any direction
  if(currentMoveVector.magnitude == 1) return true;
  else return false;
}
