#include "RecordMovePiece.hpp"

RecordMovePiece::RecordMovePiece(Colour colour, char symbol, std::string name):
                                                  Piece(colour, symbol, name){
  hasMoved = HAS_NOT_MOVED;
}


void RecordMovePiece::updateStatus(){
  hasMoved = HAS_MOVED;
}


int RecordMovePiece::getStatus(){
  return hasMoved;
}
