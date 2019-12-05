#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.hpp"

class Queen: public Piece{

public:
  Queen(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;
};


#endif
