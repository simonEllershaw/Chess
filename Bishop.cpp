#include "Bishop.hpp"
#include "Helper.hpp"

Bishop::Bishop(Colour colour): Piece(colour, SYMBOL_BISHOP){}

bool Bishop::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  if(currentMoveVector.isDiagonal()) return true;
  else return false;
}
