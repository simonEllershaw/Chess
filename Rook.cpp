#include "Rook.hpp"
#include "Helper.hpp"

Rook::Rook(Colour colour): Piece(colour, SYMBOL_ROOK, "Rook"){}

bool Rook::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  if(currentMoveVector.isHorizontal() || currentMoveVector.isVertical()){
    return true;
  }
  else return false;
}
