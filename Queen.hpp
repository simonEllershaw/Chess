#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.hpp"

class Queen: public Piece{

public:
  Queen(Colour color);

  /* Returns true if move is straight. False otherwise */
  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                      const Piece* pieceToTake) const override;
};


#endif
