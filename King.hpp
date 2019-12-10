#ifndef KING_H
#define KING_H

#include "RecordMovePiece.hpp"

class King: public RecordMovePiece{

public:
  King(Colour color);

  /* Returns true if shape specified by moveVector is a move of 1 position.
    Returns false otherwise */
  int moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};


#endif
