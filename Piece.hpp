#ifndef PIECE_H
#define PIECE_H

#include"Position.hpp"
#include"Helper.hpp"
#include"MoveVector.hpp"
#include<ostream>
#include<list>
#include<string>

class Piece{

protected:
  Colour colour;
  char symbol;
  std::string name;

public:
  Piece(Colour colour, char symbol, std::string name);

  /* Returns piece's colour */
  Colour getColour() const;

  /* Returns piece's symbol */
  char getSymbol() const ;

  /* Returns true if moveShape specified by the moveVector is valid.
    False otherwise */
  virtual bool moveShapeIsValid(const MoveVector& currentMoveVector,
                                const Piece* pieceToTake) const = 0;


  /* Returns a list of positions visted by the piece to make a move fromPosition
      by the currentMoveVector */
  virtual std::list<Position> getPositionsVistedByMove
      (const Position& fromPosition, const MoveVector& currentMoveVector) const;

  /* Update internal status of piece after it has been moved */
  virtual void updateStatus(){};

  /* Returns ostream representation of piece e.g White Rook -> WR
    Used when printing board*/
  friend std::ostream& operator<<(std::ostream & o, const Piece& p);

  /* Returns string representation of piece e.g White's Rook
    Used when handling processCodes*/
  std::string toString() const;

  virtual ~Piece(){};
};



#endif
