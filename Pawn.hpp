#ifndef PAWN_H
#define PAWN_H

#include "Piece.hpp"

class Pawn: public Piece{
bool hasMoved;

public:
  Pawn(Colour color);

  /* Returns true if:
      1) Moves 1 position forward vertically not taking a piece
      2) Moves 2 positions foward vertically not taking a piece on it's 1st move
      3) Moves 1 square diagionally taking a piece
    False otherwise */
  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;

  /* Records that the pawn hasMoved */
  void updateStatus() override;
};

#endif
