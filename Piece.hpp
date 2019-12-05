#ifndef PIECE_H
#define PIECE_H

#include"Position.hpp"
#include"Helper.hpp"
#include"MoveVector.hpp"
#include<ostream>
#include<list>

class Piece{

protected:
  Colour colour;
  char symbol;


public:
  Piece(Colour colour, char symbol);

  Colour getColour();

  char getSymbol();

  virtual bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                                  const Piece* pieceToTake) = 0;

  virtual std::list<Position> getPositionsVistedByMove
            (const Position& fromPosition, const MoveVector& currentMoveVector);

  virtual void updateStatus(){};

  friend std::ostream& operator<<(std::ostream & o, const Piece& p);

  virtual ~Piece(){};
};



#endif
