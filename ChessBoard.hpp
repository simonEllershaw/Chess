#ifndef BOARD_H
#define BOARD_H

#include "Helper.hpp"
#include "Piece.hpp"

const int lengthInputStrings = 3;

struct Player{
  Position* kingsPosition;
  bool inCheck;
  Colour colour;
  Player* opponent;
};

class ChessBoard{
  Piece* board[SIZEOFBOARD][SIZEOFBOARD] = {nullptr};
  Player whitePlayer, blackPlayer;
  Player* currentPlayer = &whitePlayer;

  public:
    ChessBoard();

    /* Takes an input and position to move to and attempts to update the board
      state accordingly. The move or the error caused by it are outputted to
      the command line  */
    void submitMove(const char fromPosInput[lengthInputStrings],
                    const char toPosInput[lengthInputStrings]);

    void resetBoard();


    ~ChessBoard();
  private:
    /* Places pieces in their intial position on the board */
    void setPiecesIntialPositions();

    /* Returns true if the input is of the form "A-H1-9".
      Otherwise returns false */
    static int inputPositionIsValid(const char
                                            inputPosition[lengthInputStrings]);

    /*  Map input char to position struct e.g. A1 -> {0,0}*/
    int convertCharToPosition(const char charPosition[lengthInputStrings],
                                            Position& position);

    /* Deletes all pieces currently stored in the baord array */
    void deleteAllPieces();

    /* Prints a representation of the current board state to the command line*/
    friend std::ostream& operator<<(std::ostream & o, const ChessBoard& cb);

    static void printHorizontalLine();

    /* Returns pointer to the piece at the piecePosition. Return a nullptr if
      no piece is present */
    Piece* getPiece(Position piecePosition) const;

    /* Takes piece off board but does not delete it from memory. Returns false
      if the piece to be taken is of the same colour as the current player.
      Returns true otherwise */
    int takePiece(Position piecePosition, Piece* pieceToTake);

    /* Moves piece on board from the fromPosition to the toPosition */
    void movePiece(Position fromPosition, Position toPosition);

    /* Returns true if the piece that is trying to be moved is of the correct
      colour and move is of the correct shape. Otherwise returns false. */
    bool moveIsAllowedByPiece(Piece* pieceToMove, Position fromPosition,
                                                    Position toPosition);

    /* Returns SUCESS if pieceToMove points at a piece (not a nullptr)
      of the correct colour. NO_PIECE_IN_SQUARE and INCORRECT_PIECE_COLOUR
      returned if either of these conditions are broken */
    int movingValidPiece(Piece* pieceToMove);


    /* Returns board to state before a move was made. */
    void undoMove(const Position toPosition, const Position fromPosition,
                  Piece* takenPiece, Player* opponent);

    /* Makes move and updates state of the chessboard returning MOVE_MADE.
      If move cannot be made due to chess logic an error code is returned. */
    int makeMove(Position fromPosition, Position toPosition);

    /* Takes a processCode and outputs an informative message to the command
      line */
    static void handleProcessCode(int errorCode, Position toPosition,
                                                        Position fromPosition);

    /* Returns true if player is in check. False otherwise */
    bool playerIsInCheck(Player* currentPlayer);

    /* Returns true if player is in checkmate. False otherwise */
    bool playerIsInCheckmate(Player* currentPlayer);

    /* Returns true if player is in stalemate. False otherwise */
    bool playerIsInStalemate(Player* currentPlayer);

    bool pieceInTheWay(Piece* pieceToMove, Position fromPosition,
                                                        Position toPosition);

};

#endif
