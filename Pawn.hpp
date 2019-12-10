#ifndef PAWN_H
#define PAWN_H

#include "RecordMovePiece.hpp"

class Pawn: public RecordMovePiece{

public:
  Pawn(Colour color);

  /* Returns true if:
      1) Moves 1 position forward vertically not taking a piece
      2) Moves 2 positions foward vertically not taking a piece on it's 1st move
      3) Moves 1 square diagionally taking a piece
    False otherwise */
  int moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};

#endif
