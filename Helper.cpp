#include"Helper.hpp"

Position whiteToBlackStartPos(const Position& whiteStartPosition){
  // Black start positions are a reflection of white start positions around
  // board mid point: (midpoint - whitePos) + midpoint = SIZEOFBOARD - whitePos
  // -1 is required as 0 indexed
  return {whiteStartPosition.column, SIZEOFBOARD - whiteStartPosition.row - 1};
}


std::ostream& operator<<(std::ostream & o, const Colour& c){
  if(c == WHITE) return o << "White";
  else return o << "Black";
}
