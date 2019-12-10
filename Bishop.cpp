#include "Bishop.hpp"
#include "Helper.hpp"

Bishop::Bishop(Colour colour): Piece(colour, SYMBOL_BISHOP, "Bishop"){}

int Bishop::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  if(currentMoveVector.isDiagonal()) return true;
  else return false;
}
