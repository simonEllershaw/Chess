#include "Knight.hpp"
#include "Helper.hpp"

Knight::Knight(Colour colour): Piece(colour, SYMBOL_KNIGHT){}

bool Knight::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  // King can move 1 square in any direction
  if(currentMoveVector.is2x1LShape()) return true;
  else return false;
}

std::list<Position> Knight::getPositionsVistedByMove
            (const Position& fromPosition, const MoveVector& currentMoveVector){
  return {};
}
