#include "Piece.hpp"
#include <algorithm>
#include <iostream>

Piece::Piece(Colour colour): colour(colour){};

Colour Piece::getColour(){
  return colour;
}

std::list<Position> Piece::getStartingPositions(){
  return startingPositions;
}


bool Piece::moveShapeIsValid(const Position& fromPosition,
                                            const Position& toPosition){
  return true;
};

std::list<Position> Piece::getSquaresBetween2Positions(const Position& fromPosition,
                                                  const Position& toPosition){
  std::list<Position> squaresBetweenPositions;

  const Position differenceVector = {toPosition.column - fromPosition.column,
                                          toPosition.row - fromPosition.row};
  const int magnitude= std::max(abs(differenceVector.column),
                                                    abs(differenceVector.row));
  const Position normalVector = {differenceVector.column / magnitude,
                                            differenceVector.row / magnitude};

  for(int squareNum = 1; squareNum < magnitude; squareNum++){
    int throughSquareCol = fromPosition.column + squareNum*normalVector.column;
    int throughSquareRow = fromPosition.row + squareNum*normalVector.row;
    squaresBetweenPositions.push_back({throughSquareCol, throughSquareRow});
  }

  return squaresBetweenPositions;
};

std::ostream& operator<<(std::ostream & o, const Piece& p){
  char colourSymbol;
  if(p.colour==WHITE) colourSymbol = 'W';
  else colourSymbol = 'B';
  return o << colourSymbol << p.symbol;
}
