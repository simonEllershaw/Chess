#ifndef PAWN_H
#define PAWN_H

#include "Piece.hpp"

class Pawn: public Piece{
bool hasMoved;

public:
  Pawn(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;

  void updateStatus() override;
};


#endif
