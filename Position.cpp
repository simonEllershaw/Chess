#include "Position.hpp"


void Position::getNormAndMagToPos(Position& otherPosition, Vector& normal, int& magnitude){

  const Position diffInPos = otherPosition - *(this);
  magnitude= std::max(abs(diffInPos.column), abs(diffInPos.row));
  normal = {int(diffVector.column / magnitude), int(diffVector.row / magnitude)};
}

Position Position::operator-(Position& otherPosition){
  return {column - otherPosition.column, row - otherPosition.row};
}

std::ostream& operator<<(std::ostream & o, Position& p){
  return o << p.column << p.row << std::endl;
}
