#ifndef ROOK_H
#define ROOK_H

#include "Piece.hpp"

class Rook: public Piece{

public:
  Rook(Colour color);

  /* Returns true if move is horizontal or vertical. Returns false otherwise */
  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};
#endif
