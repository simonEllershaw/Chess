#ifndef PLAYER_H
#define PLAYER_H

#include"Position.hpp"
#include"ChessBoard.h"
#include"Helper.hpp"

class ChessBoard;

class Player{
  Position kingsPosition;
  Colour colour;
  Player* opponent;

  /* Checks if move is allowed by the rules of chess. Does not ensure if miving
    into check Returns SUCESS or an appropriate error code */
  int moveIsLegal(const Position& fromPosition, const Position& toPosition,
                  ChessBoard* board);

  /* Returns true if castling move is valid and moves castle to castled position.
    Otherwise returns false and castle is unmoved */
  bool castleIsValid(const Position& fromPosition, const Position& toPosition,
                                                          ChessBoard* board);

  /* Checks if moving a piece and if of the correct colour. Returns SUCESS or
    an appropriate error code */
  int movingValidPiece(Piece* pieceToMove) const;

  /* Returns true if King can legally move. False otherwise*/
  bool kingCanMove(ChessBoard* board);

  /* Returns if all attacks (if there are any) on the king can be stopped
    False otherwiese */
  bool stopAttacksOnKing(ChessBoard* board);

  /* Returns true if postion or squares between the position and King can be
    reached legally. False otherwise*/
  bool canTakeOrBlockPathToKing(Position& positionAttackingKing, ChessBoard* board);

  /* Returns true can legally move toPosition. False otherwise */
  bool canMakeMoveToPosition(const Position& toPosition, ChessBoard* board);

  /* Returns true if a legal move can be made fromPosition. False otherwiese */
  bool canMakeMoveFromPosition(const Position fromPosition, ChessBoard* board);

  /* Checks if kingsPosition is correct if updates kingsPosition
    to lastMovedToPosition */
  void updateKingsPosition(const ChessBoard* board,
                                            const Position lastMovedToPosition);
public:
  Player(Position kingsPosition, Colour colour, Player* opponent);

  Player* getOpponent() const;

  Colour getColour() const;

  void setOpponent(Player* opponent);

  /* Attempts to make move. Returns SUCCESS or appropriate errorCode. */
  int makeMove(const Position& fromPosition, const Position& toPosition,
              ChessBoard* board);

  /* Returns true if player is in checkmate. False otherwise */
  bool inCheckmate(ChessBoard* board);

  /* Returns true if player is in stalemate. False otherwise */
  bool inStalemate(ChessBoard* board);

  /* Returns first foudn position attacking the king. NOT_IN_CHECK otherwise */
  Position inCheck(ChessBoard* board);

  /* Returns ostream representation of the player*/
  friend std::ostream& operator<<(std::ostream & o, const Player& pl);

  /* Resets player's internal state to it's starting state */
  void reset();
};

#endif
