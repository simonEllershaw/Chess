#ifndef KING_H
#define KING_H

#include "Piece.hpp"

class King: public Piece{

public:
  King(Colour color);

  /* Returns true if shape specified by moveVector is a move of 1 position.
    Returns false otherwise */
  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};


#endif
