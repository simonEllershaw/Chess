#include "King.hpp"
#include "Helper.hpp"

King::King(Colour colour): RecordMovePiece(colour, SYMBOL_KING, "King"){}

int King::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  // King can move 1 square in any direction
  if(currentMoveVector.magnitude == 1) return true;
  else if(currentMoveVector.magnitude == 2 && currentMoveVector.isHorizontal()){

    return CASTLING;
  }
  else return false;
}
