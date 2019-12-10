#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.hpp"

class Knight: public Piece{

public:
  Knight(Colour color);

  /* Returns true if shape specified by moveVector is 'L-Shaped'.
    Returns false otherwise */
  int moveShapeIsValid(const MoveVector& currentMoveVector,
                                    const Piece* pieceToTake) const override;

  /* Returns an empty list as a knight jumps over all pieces */
  std::list<Position> getPositionsVistedByMove(const Position& fromPosition,
                            const MoveVector& currentMoveVector) const override;
};


#endif
