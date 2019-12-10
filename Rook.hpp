#ifndef ROOK_H
#define ROOK_H

#include "RecordMovePiece.hpp"

class Rook: public RecordMovePiece{

public:
  Rook(Colour color);

  /* Returns true if move is horizontal or vertical. Returns false otherwise */
  int moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};


#endif
