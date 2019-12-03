#include "Piece.hpp"

Piece::Piece(Colour colour): colour(colour){};

Colour Piece::getColour(){
  return colour;
}

std::list<Position> Piece::getStartingPositions(){
  return startingPositions;
}


bool Piece::moveShapeIsValid(const Position fromPosition,
                                            const Position toPosition){
  return true;
};

std::list<Position> Piece::getSquaresBetween2Positions(const Position fromPosition,
                                                  const Position toPosition){
return {{0,0}};
};

std::ostream& operator<<(std::ostream & o, const Piece& p){
  char colourSymbol;
  if(p.colour==WHITE) colourSymbol = 'W';
  else colourSymbol = 'B';
  return o << colourSymbol << p.symbol;
}
