Player(Colour playerColour);


void makeMove(const Position& posOriginal, const Position& posToMoveTo
              Piece& board[SIZEOFBOARD][SIZEOFBOARD]){
  Piece* pieceToMove =  board[posOriginal.row][posOriginal.column];
  if(moveIsLegal(pieceToMove, posToMoveTo, board))
};


static bool moveIsLegal(const Position& posOriginal,
                        const Position& posToMoveTo, ChessBoard& cb){
  return true;
}


bool isInCheck(const ChessBoard& cb){
  return false;
}

~Player();
