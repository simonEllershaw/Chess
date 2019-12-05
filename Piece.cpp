#include "Piece.hpp"
#include <algorithm>
#include <iostream>

Piece::Piece(Colour colour, char symbol): colour(colour), symbol(symbol){}

Colour Piece::getColour(){
  return colour;
}

char Piece::getSymbol(){
  return symbol;
}

std::list<Position> Piece::getPositionsVistedByMove
            (const Position& fromPosition, const MoveVector& currentMoveVector){

  std::list<Position> positionsVisited;
  for(int scaleFactor = 1; scaleFactor < currentMoveVector.magnitude; scaleFactor++){
    int throughSquareCol = fromPosition.column
                            + scaleFactor*currentMoveVector.normalVector.column;
    int throughSquareRow = fromPosition.row
                              + scaleFactor*currentMoveVector.normalVector.row;
    positionsVisited.push_back({throughSquareCol, throughSquareRow});
  }
  return positionsVisited;
}

std::ostream& operator<<(std::ostream & o, const Piece& p){
  char colourSymbol;
  if(p.colour==WHITE) colourSymbol = 'W';
  else colourSymbol = 'B';
  return o << colourSymbol << p.symbol;
}
