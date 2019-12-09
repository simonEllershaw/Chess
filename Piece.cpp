#include "Piece.hpp"
#include <algorithm>
#include <iostream>

Piece::Piece(Colour colour, char symbol, std::string name):
                                  colour(colour), symbol(symbol), name(name){}

Colour Piece::getColour() const{
  return colour;
}

char Piece::getSymbol() const{
  return symbol;
}

std::list<Position> Piece::getPositionsVistedByMove
                                    (const Position& fromPosition,
                                    const MoveVector& currentMoveVector) const{
  std::list<Position> positionsVisited;
  // Iterate across currentMoveVector's normalVector increasing the scaleFactor
  // by 1 each time. Recording the squares vistied.
  for(int scaleFactor = 1; scaleFactor < currentMoveVector.magnitude;
    scaleFactor++){
    int throughSquareCol = fromPosition.column
                            + scaleFactor*currentMoveVector.normalVector.column;
    int throughSquareRow = fromPosition.row
                              + scaleFactor*currentMoveVector.normalVector.row;
    positionsVisited.push_back({throughSquareCol, throughSquareRow});
  }
  return positionsVisited;
}

std::string Piece::toString() const{
  std::string colourSymbol;
  if(colour==WHITE) colourSymbol = "W";
  else colourSymbol = "B";
  return colourSymbol + symbol;
}

std::ostream& operator<<(std::ostream & o, const Piece& p){
  return o << p.colour << "'s " << p.name;
}
