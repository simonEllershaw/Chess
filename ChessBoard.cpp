#include<list>
#include<iterator>
#include<iostream>
#include<string>
#include<typeinfo>
#include"ChessBoard.hpp"
#include"Rook.hpp"
#include"Bishop.hpp"
#include"Helper.hpp"
#include"Queen.hpp"
#include"King.hpp"
#include"Knight.hpp"
#include"Pawn.hpp"


ChessBoard::ChessBoard(){
  setPiecesIntialPositions();
  whitePlayer = new Player(WHITE_START_POS_KING.front(), WHITE, NULL);
  blackPlayer = new Player(whiteToBlackStartPos(WHITE_START_POS_KING.front()),
                                                           BLACK, whitePlayer);
  whitePlayer->setOpponent(blackPlayer);
  currentPlayer = whitePlayer;
  startGameMsg = "A new chess game is started!";
  std::cout << startGameMsg << std::endl;
}

ChessBoard::~ChessBoard(){
  deletePiecesOnBoard();
  deleteSavedToPositions();
  delete whitePlayer;
  delete blackPlayer;
}

void ChessBoard::resetBoard(const bool& noPawns){
  // Delete replace pieces
  deletePiecesOnBoard();
  deleteSavedToPositions();
  setPiecesIntialPositions(noPawns);

  // Reset player states
  whitePlayer->reset();
  blackPlayer->reset();
  currentPlayer = whitePlayer;

  std::cout << startGameMsg << std::endl;
}


void ChessBoard::submitMove(std::string fromPosInput, std::string toPosInput)
{
  Position fromPosition, toPosition;
  int processCode;

  // Read in positions
  if(convertCharToPosition(fromPosInput, fromPosition)) return;
  if(convertCharToPosition(toPosInput, toPosition)) return;

  // Make and handle outcome of move
  processCode = currentPlayer->makeMove(fromPosition, toPosition, this);
  if(processCode != SUCCESS){
    handleProcessCode(processCode, fromPosition, toPosition);
  }
  else{
    getPiece(toPosition)->updateStatus();
    handleProcessCode(SUCCESS, fromPosition, toPosition);

    // Switch to next player and see if in checkmate or stalemate
    currentPlayer = currentPlayer->getOpponent();
    if(currentPlayer->inCheckmate(this)){
      handleProcessCode(CHECKMATE, fromPosition, toPosition);
    }
    else if(currentPlayer->inStalemate(this)){
      handleProcessCode(STALEMATE, fromPosition, toPosition);
    }
  }
}

bool ChessBoard::pieceInTheWay(Piece* pieceToMove, const Position& fromPosition,
                                          const MoveVector& currentMoveVector){
  std::list<Position> positionsToMoveThrough = pieceToMove
                ->getPositionsVistedByMove(fromPosition, currentMoveVector);
  // Iterate through positions and return true if a piece on any of them
  for(auto it = positionsToMoveThrough.begin(); it != positionsToMoveThrough.end();
      ++it){
    if(getPiece(*it) != nullptr) return true;
  }
  return false;
}

Piece* ChessBoard::getPiece(Position piecePosition) const{
  return board[piecePosition.row][piecePosition.column];
}


void ChessBoard::takePiece(Position piecePosition){
  // First check taking a piece of a different colour
  savedToPositions.push(getPiece(piecePosition));
  board[piecePosition.row][piecePosition.column] = nullptr;
}


void ChessBoard::movePiece(Position fromPosition, Position toPosition){
  // Always take piece even if nothing is there so stack can be updated for
  // backtracking
  takePiece(toPosition);
  board[toPosition.row][toPosition.column] = getPiece(fromPosition);
  board[fromPosition.row][fromPosition.column] = nullptr;
}


void ChessBoard::deletePiecesOnBoard(){
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(board[row][column]!=nullptr){
        delete board[row][column];
        // Replace with empty position
        board[row][column] = nullptr;
      }
    }
  }
}

void ChessBoard::deleteSavedToPositions(){
  Piece* takenPiece;
  while(!savedToPositions.empty()){
    takenPiece = savedToPositions.top();
    savedToPositions.pop();
    // Nullptr on stack to allow backtracking
    if(takenPiece != nullptr) delete takenPiece;
  }
}


void ChessBoard::setPiecesIntialPositions(const bool& noPawns){
  initPieceType<Rook>(WHITE_START_POS_ROOK);
  initPieceType<Bishop>(WHITE_START_POS_BISHOP);
  initPieceType<Queen>(WHITE_START_POS_QUEEN);
  initPieceType<King>(WHITE_START_POS_KING);
  initPieceType<Knight>(WHITE_START_POS_KNIGHT);
  // No pawns condition only used to make testing easier
  if(!noPawns) initPieceType<Pawn>(WHITE_START_POS_PAWN);
}

template<class pieceType> void ChessBoard::initPieceType
                                  (std::list<Position> whiteStartingPositions){
  for(auto it = whiteStartingPositions.begin();
                                      it != whiteStartingPositions.end(); ++it){
    // Make and place white and opposing black piece
    board[it->row][it->column] = new pieceType(WHITE);
    const Position blackStartPos = whiteToBlackStartPos(*it);
    board[blackStartPos.row][blackStartPos.column] = new pieceType(BLACK);
  }
}


int ChessBoard::inputPositionIsValid(std::string inputPosition){
  std::string errorMessage = inputPosition + " is an invalid input. " +
                            "Move cannot be made. Position values are between" +
                            " A1 and H8.";
  if(inputPosition.length() != LENGTH_INPUT_STRINGS){
    std::cout << errorMessage << std::endl;
    return INVALID_INPUT_POSITION;
  }
  if(inputPosition[0] < 'A' || inputPosition[0] > 'H'){
    std::cout << errorMessage << std::endl;
    return INVALID_INPUT_POSITION;
  }
  else if(inputPosition[1] < '1' || inputPosition[1] > '8'){
    std::cout << errorMessage << std::endl;
    return INVALID_INPUT_POSITION;
  }
  else return SUCCESS;
}


int ChessBoard::convertCharToPosition(std::string stringPosition,
                                        Position& position){
  int errorCode = inputPositionIsValid(stringPosition);
  if(errorCode) return errorCode;

  // Position in format {column, row}, {0,0} in bottom left corner of board = {A,1}
  position = {stringPosition[0] - (int) 'A',  stringPosition[1] - (int) '1'};
  return SUCCESS;
}

void ChessBoard::undoMove(const Position fromPosition, const Position toPosition){
  board[fromPosition.row][fromPosition.column] =
                                      board[toPosition.row][toPosition.column];
  // Use savedToPositions for backtracking
  board[toPosition.row][toPosition.column] = savedToPositions.top();
  savedToPositions.pop();
}

void ChessBoard::handleProcessCode(const int processCode,
                                  const Position& fromPosition,
                                  const Position& toPosition) const{
  std::string errorMessage;
  switch(processCode){
    case(NO_PIECE_IN_SQUARE):
        std::cout << "There is no piece at position " << fromPosition<< "!";
        break;
    case(INCORRECT_PIECE_COLOUR):
      std::cout << "It's not " << *(currentPlayer) << "'s turn to move!";
      break;
    case(TAKING_OWN_PIECE):
      std::cout << *currentPlayer << " is trying to take their own piece at "
                << toPosition << "!"; break;
    case(PIECE_IN_THE_WAY):
    case(INVALID_MOVE):
      std::cout << *(getPiece(fromPosition)) << " cannot move to "<<
                toPosition << "!"; break;
    case(MOVE_INTO_CHECK):
      std::cout << *(getPiece(fromPosition)) << " cannot move to " <<
              toPosition << "(leaves "<< *currentPlayer << " in check)!"; break;
    case(CHECKMATE):
      std::cout << *currentPlayer << " is in checkmate"; break;
    case(STALEMATE):
      std::cout << *currentPlayer << " is in stalemate"; break;
    case(SUCCESS):
      std::cout << *(getPiece(toPosition)) << " moves from " << fromPosition
                << " to " << toPosition; break;
    default: errorMessage = "Unknown processCode " + std::to_string(processCode);
  }
    std::cout << std::endl;
}

std::string ChessBoard::convertPositionToChar(const Position& orgPosition){
  return {char(orgPosition.column + 'A'), char(orgPosition.row + '1'), '\0'};
}


/* Prints a representation of the current board state to the command line*/
std::ostream& operator<<(std::ostream & o, const ChessBoard& cb){
  Piece* pieceInSquare;
  char colLetter = 'A', divider = '|';

  // Print reverse row order as 0,0 -> A1 which is in bottom left corner
  for(int row = SIZEOFBOARD - 1; row >= 0; row--){
    cb.printHorizontalLine(o);
    // Row number (not 0 indexed)
    o << row+1 << divider;
    for(int col=0; col < SIZEOFBOARD; col++){
      // Get piece and output representation. No piece is just empty
      pieceInSquare = cb.getPiece({col,row});
      if(pieceInSquare == nullptr) o << "  ";
      else o << pieceInSquare->toString();
      o << divider;
    }
    o  << std::endl;
  }

  // Output column letters at bottom of board
  for(int col=0; col<SIZEOFBOARD; col++){
    o << "  " << colLetter;
    colLetter ++;
  }
  o << std::endl;

  return o << "WILL BE FIXED";
}

void ChessBoard::printHorizontalLine(std::ostream & o){
  o << " ";
  for(int col=0; col<SIZEOFBOARD; col++){
    o <<"___";
  }
  o << std::endl;
}
