#ifndef KING_H
#define KING_H

#include "Piece.hpp"

class King: public Piece{

public:
  King(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;
};


#endif
