#include "Pawn.hpp"
#include "Helper.hpp"


Pawn::Pawn(Colour colour): Piece(colour, SYMBOL_PAWN){
  hasMoved = false;
}

bool Pawn::moveShapeIsValid(const MoveVector& currentMoveVector,
                                          const Piece* pieceToTake){
  // Ensure moving in forward direction w.r.t colour (white = 1, black= -1)
  if(currentMoveVector.normalVector.row != colour) return false;
  // Can move 1 position vertically or 2 on the first move but cannot take
  else if(currentMoveVector.isVertical() && pieceToTake == nullptr){
    if(currentMoveVector.magnitude == 1) return true;
    else if(currentMoveVector.magnitude == 2 && !hasMoved) return true;
  }
  // Can take pieces 1 piece diagonally away
  else if(pieceToTake != nullptr && currentMoveVector.isDiagonal()
          && currentMoveVector.magnitude == 1) return true;
  return false;
}

void Pawn::updateStatus(){
  hasMoved = true;
}
