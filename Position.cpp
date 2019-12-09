#include "Position.hpp"

Position Position::operator-(const Position& otherPosition){
  return {column - otherPosition.column, row - otherPosition.row};
}

bool Position::operator==(const Position& otherPosition) const{
  if(otherPosition.column!=column) return false;
  else if(otherPosition.row!=row) return false;
  else return true;
}

bool Position::operator!=(const Position& otherPosition) const{
  return !(*this == otherPosition);
}

std::ostream& operator<<(std::ostream & o, const Position& p){
  return o << char(p.column + 'A') << char(p.row + '1');
}
