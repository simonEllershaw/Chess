#ifndef MOVE_VECTOR_H
#define MOVE_VECTOR_H

#include<ostream>
#include"Position.hpp"

struct MoveVector{
  Position diffInPositions;
  Position normalVector;
  int magnitude;

  MoveVector(Position fromPosition, Position toPosition);

  bool isDiagonal() const;

  bool isVertical() const;

  bool isHorizontal() const;

  bool is2x1LShape() const;

};

#endif
