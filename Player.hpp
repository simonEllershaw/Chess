#ifndef PLAYER_H;
#define PLAYER_H;

#include "Helper.hpp";

class Player{
  Position* kingsPosition;
  bool inCheck;
  Colour colour;
  Player* opponent;

public:
  Player(Colour playerColour);

  /* Makes move if it breaks no rules of chess. Messages are printed to the
    command line to confirm a sucessful move or the error that occured */
  void makeMove(const Position& posOriginal, const Position& posToMoveTo
                Piece& board[SIZEOFBOARD][SIZEOFBOARD]);

  /* Returns true if move breaks no rules of chess, false otherwise */
  static bool moveIsLegal(const Position& posOriginal,
                          const Position& posToMoveTo, ChessBoard& cb);


  /* Returns true if player is in check and false otherwise */
  bool isInCheck(const ChessBoard& cb);

  ~Player();

private:



};

#endif;
