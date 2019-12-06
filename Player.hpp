#ifndef PLAYER_H
#define PLAYER_H

#include"Position.hpp"
#include"ChessBoard.hpp"
#include"Helper.hpp"

class ChessBoard;

class Player{
  Position kingsPosition;
  bool checkStatus;
  Colour colour;
  Player* opponent;

  int movingValidPiece(Piece* pieceToMove);

  int moveIsLegal(const Position& fromPosition, const Position& toPosition,
                  ChessBoard* board);

  bool canMakeMoveFromPosition(const Position fromPosition, ChessBoard* board);

  /* Returns true if player is in check. False otherwise */
  Position inCheck(ChessBoard* board);

  bool stopAttacksOnKing(ChessBoard* board);

  bool canTakeOrBlockPathToKing(Position& positionAttackingKing, ChessBoard* board);

  bool canMakeMoveToPosition(const Position toPosition, ChessBoard* board);

  bool kingCanMove(ChessBoard* board);

public:
  Player(Position kingsPosition, Colour colour, Player* opponent);

  int makeMove(const Position& fromPosition, const Position& toPosition,
              ChessBoard* board);

  Player* getOpponent() const;

  Colour getColour() const;

  void setCheck(const bool& checkStatus);

  void setOpponent(Player* opponent);

  void setKingPosition(Position& kingsPosition);

  Position getKingsPosition(const ChessBoard* board);

  void updateKingsPosition(const ChessBoard* board);

  void reset();

  /* Returns true if player is in checkmate. False otherwise */
  bool inCheckmate(ChessBoard* board);

  /* Returns true if player is in stalemate. False otherwise */
  bool inStalemate(ChessBoard* board);

};

#endif
