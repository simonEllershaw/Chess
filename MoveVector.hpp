#ifndef MOVE_VECTOR_H
#define MOVE_VECTOR_H

#include<ostream>
#include"Position.hpp"

/* Struct is loosely based on basic vector mathematics. Major difference is
  that when calculalting normalVector the squares are added up instead of
  using pythagoreas */ 

struct MoveVector{
  Position diffInPositions;
  Position normalVector; // Can be equal to MOVE_NOT_STRAIGHT
  int magnitude;

  MoveVector(Position fromPosition, Position toPosition);

  /* Returns true if normal vector has an equal x, y componenet
    false otherwise.*/
  bool isDiagonal() const;

  /* Returns true if normal vector has no x componenet and false otherwise.*/
  bool isVertical() const;

  /* Returns true if normal vector has no y componenet and false otherwise.*/
  bool isHorizontal() const;

  /* Returns true if moveVector corresponds to an 'L-shape'*/
  bool isLShaped() const;

};

#endif
