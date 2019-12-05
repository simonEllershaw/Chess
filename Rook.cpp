#include "Rook.hpp"
#include "Helper.hpp"

Rook::Rook(Colour colour): Piece(colour, SYMBOL_ROOK){}

bool Rook::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  if(currentMoveVector.isHorizontal() || currentMoveVector.isVertical()){
    return true;
  }
  else return false;
}
