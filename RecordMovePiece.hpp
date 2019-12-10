#ifndef RECORDMOVE_H
#define RECORDMOVE_H

#include "Piece.hpp"
#include "Helper.hpp"
#include<string>

class RecordMovePiece: public Piece{
protected:
  int hasMoved;

public:
  RecordMovePiece(Colour colour, char symbol, std::string name);

  /* Records that the piece hasMoved */
  void updateStatus() override;

  /* Returns true if piece has moved false otherwise */
  int getStatus() override;
};


#endif
