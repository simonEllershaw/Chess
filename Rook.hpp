#ifndef ROOK_H
#define ROOK_H

#include "Piece.hpp"

class Rook: public Piece{

public:
  Rook(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;

};


#endif
