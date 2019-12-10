#include "RecordMovePiece.hpp"

RecordMovePiece::RecordMovePiece(Colour colour, char symbol, std::string name):
                                                  Piece(colour, symbol, name){
  hasMoved = HAS_NOT_MOVED;
}

/* Records that the piece hasMoved */
void RecordMovePiece::updateStatus(){
  hasMoved = HAS_MOVED;
}

/* Returns true if piece has moved false otherwise */
int RecordMovePiece::getStatus(){
  return hasMoved;
}
