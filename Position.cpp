#include "Position.hpp"

Position Position::operator-(const Position& otherPosition){
  return {column - otherPosition.column, row - otherPosition.row};
}

std::ostream& operator<<(std::ostream & o, const Position& p){
  return o << p.column << " " << p.row;
}

bool Position::operator==(const Position& otherPosition) const{
  if(otherPosition.column!=column) return false;
  if(otherPosition.row!=row) return false;
  return true;
}

bool Position::operator!=(const Position& otherPosition) const{
  return !(*this == otherPosition);
}
