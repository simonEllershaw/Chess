#include "Rook.hpp"
#include "Helper.hpp"

Rook::Rook(Colour colour): RecordMovePiece(colour, SYMBOL_ROOK, "Rook"){}

int Rook::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  if(currentMoveVector.isHorizontal() || currentMoveVector.isVertical()){
    return true;
  }
  else return false;
}
