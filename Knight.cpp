#include "Knight.hpp"
#include "Helper.hpp"

Knight::Knight(Colour colour): Piece(colour, SYMBOL_KNIGHT, "Knight"){}

int Knight::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake) const{
  // King can move 1 square in any direction
  if(currentMoveVector.isLShaped()) return true;
  else return false;
}

std::list<Position> Knight::getPositionsVistedByMove (const Position&
                      fromPosition, const MoveVector& currentMoveVector) const{
  return {};
}
