#ifndef PIECE_H
#define PIECE_H

#include"Position.hpp"
#include"Helper.hpp"
#include<ostream>
#include<list>

class Piece{

protected:
  std::list<Position> startingPositions;
  char symbol;
  Colour colour;

public:
  Piece(Colour colour);

  Colour getColour();

  std::list<Position> getStartingPositions();

  virtual bool moveShapeIsValid(const Position& fromPosition,
                                                const Position& toPosition);

  virtual std::list<Position> getSquaresBetween2Positions
                  (const Position& fromPosition, const Position& toPosition);

  friend std::ostream& operator<<(std::ostream & o, const Piece& p);
};




#endif
