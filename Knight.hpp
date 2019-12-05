#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.hpp"

class Knight: public Piece{

public:
  Knight(Colour color);

  bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                            const Piece* pieceToTake) override;

  std::list<Position> getPositionsVistedByMove(const Position& fromPosition,
                                  const MoveVector& currentMoveVector) override;
};


#endif
