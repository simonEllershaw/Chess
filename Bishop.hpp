#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.hpp"

class Bishop: public Piece{

public:
  Bishop(Colour color);

  /* Returns true if shape specified by moveVector is a diagonaal.
    Returns false otherwise */
  int moveShapeIsValid(const MoveVector& currentMoveVector,
                                    const Piece* pieceToTake) const override;
};


#endif
