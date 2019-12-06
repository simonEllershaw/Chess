#ifndef BOARD_H
#define BOARD_H

#include "Helper.hpp"
#include "Piece.hpp"
#include"Position.hpp"
#include"MoveVector.hpp"
#include "Player.hpp"
#include <stack>

class Player;

class ChessBoard{
  Piece* board[SIZEOFBOARD][SIZEOFBOARD] = {nullptr};
  Player* whitePlayer, *blackPlayer, *currentPlayer;
  // ALlows for backtracking
  std::stack<Piece*> savedToPositions;

  public:
    ChessBoard();

    /* Takes an input and position to move to and attempts to update the board
      state accordingly. The move or the error caused by it are outputted to
      the command line  */
    void submitMove(const char fromPosInput[LENGTH_INPUT_STRINGS],
                    const char toPosInput[LENGTH_INPUT_STRINGS]);

    void resetBoard(const bool& noPawns = false);

    /* Returns pointer to the piece at the piecePosition. Return a nullptr if
      no piece is present */
    Piece* getPiece(Position piecePosition) const;

    /* Takes piece off board */
    void takePiece(Position piecePosition);

    /* Moves piece on board from the fromPosition to the toPosition */
    void movePiece(Position fromPosition, Position toPosition);

    /* Returns board to state before a move was made. */
    void undoMove(const Position fromPosition, const Position toPosition);


    bool pieceInTheWay(Piece* pieceToMove, const Position& fromPosition,
                                          const MoveVector& currentMoveVector);

    ~ChessBoard();
  private:
    /* Places pieces in their intial position on the board */
    void setPiecesIntialPositions(const bool& noPawns = false);

    /* Returns true if the input is of the form "A-H1-9".
      Otherwise returns false */
    static int inputPositionIsValid(const char
                                            inputPosition[LENGTH_INPUT_STRINGS]);

    /*  Map input char to position struct e.g. A1 -> {0,0}*/
    int convertCharToPosition(const char charPosition[LENGTH_INPUT_STRINGS],
                                            Position& position);

    /* Deletes all pieces currently stored in the baord array */
    void deletePiecesOnBoard();

    void deleteSavedToPositions();


    /* Prints a representation of the current board state to the command line*/
    friend std::ostream& operator<<(std::ostream & o, const ChessBoard& cb);

    static void printHorizontalLine(std::ostream & o);

    /* Takes a processCode and outputs an informative message to the command
      line */
    static void handleProcessCode(int errorCode, Position toPosition,
                                                        Position fromPosition);

    template<class pieceType> void initPieceType(std::list<Position> whiteStartingPositions);
};

#endif
