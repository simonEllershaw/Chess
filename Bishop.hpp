#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.hpp"

class Bishop: public Piece{

public:
  Bishop(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;
};


#endif
