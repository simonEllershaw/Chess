#include "MoveVector.hpp"
#include "Helper.hpp"
#include<iostream>


MoveVector::MoveVector(Position fromPosition, Position toPosition){
  diffInPositions = toPosition - fromPosition;
  magnitude = std::max(abs(diffInPositions.column), abs(diffInPositions.row));

  if(diffInPositions.column % magnitude == 0
                                      && diffInPositions.row % magnitude == 0){
    normalVector = {diffInPositions.column / magnitude,
                                              diffInPositions.row / magnitude};
  }
  else{
    // Dont return error here as could be moving a knight
    normalVector = MOVE_NOT_STRAIGHT;
  }
}

bool MoveVector::isDiagonal() const{
  if(abs(normalVector.row)==1 && abs(normalVector.column)==1) return true;
  else return false;
}

bool MoveVector::isVertical() const{
  if(abs(normalVector.row)==1 && abs(normalVector.column)==0) return true;
  else return false;
}

bool MoveVector::isHorizontal() const{
  if(abs(normalVector.row)==0 && abs(normalVector.column)==1) return true;
  else return false;
}

bool MoveVector::is2x1LShape() const{
  // If move has magnitude of 2 the other componenet is either 2, 1 or 0
  // 2 and 0 result in straight moves leaving only the L shape move
  if(magnitude == 2 && normalVector == MOVE_NOT_STRAIGHT) return true;
  else return false;
}
