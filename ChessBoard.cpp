#include<list>
#include<iterator>
#include<iostream>
#include<string>
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
}


void ChessBoard::resetBoard(const bool& noPawns){
  deletePiecesOnBoard();
  deleteSavedToPositions();
  setPiecesIntialPositions(noPawns);
  whitePlayer->reset();
  blackPlayer->reset();
  currentPlayer = whitePlayer;
}


void ChessBoard::submitMove(const char fromPosInput[LENGTH_INPUT_STRINGS],
                              const char toPosInput[LENGTH_INPUT_STRINGS])
{
  Position fromPosition, toPosition;
  int processCode;

  std::cout << "From: " << fromPosInput << " To: " << toPosInput << std::endl;
  std::cout << currentPlayer->getColour() << "'s turn" << std::endl;
  // Read in positions
  if(convertCharToPosition(fromPosInput, fromPosition)) return;
  if(convertCharToPosition(toPosInput, toPosition)) return;

  processCode = currentPlayer->makeMove(fromPosition, toPosition, this);

  if(processCode != SUCCESS){
    handleProcessCode(processCode, fromPosition, toPosition);
  }
  else{
    getPiece(toPosition)->updateStatus();
    currentPlayer = currentPlayer->getOpponent();
    if(currentPlayer->inCheckmate(this)) std::cout << "CHECKMATE" << std::endl;
    else if(currentPlayer->inStalemate(this)) std::cout << "STALEMATE" << std::endl;
    else std::cout << "SUCCESS" << std::endl;
  }
}

bool ChessBoard::pieceInTheWay(Piece* pieceToMove, const Position& fromPosition,
                                          const MoveVector& currentMoveVector){
  // If square that needs to be moved through is occupied by a piece return true
  // Else false.
  std::list<Position> positionsToMoveThrough = pieceToMove
                ->getPositionsVistedByMove(fromPosition, currentMoveVector);

  for(auto it = positionsToMoveThrough.begin(); it != positionsToMoveThrough.end();
      ++it)
  {
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
  takePiece(toPosition);
  board[toPosition.row][toPosition.column] = getPiece(fromPosition);
  board[fromPosition.row][fromPosition.column] = nullptr;
}


ChessBoard::~ChessBoard(){
  deletePiecesOnBoard();
  deleteSavedToPositions();
  delete whitePlayer;
  delete blackPlayer;
}


void ChessBoard::deletePiecesOnBoard(){
  // Delete all piece on board
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(board[row][column]!=nullptr){
        delete board[row][column];
        board[row][column] = nullptr;
      }
    }
  }
}

void ChessBoard::deleteSavedToPositions(){
  Piece* takenPiece;
  // Delete taken pieces
  while(!savedToPositions.empty()){
    takenPiece = savedToPositions.top();
    savedToPositions.pop();
    if(takenPiece != nullptr) delete takenPiece;
  }
}


/* Places pieces in their intial position on the board */
void ChessBoard::setPiecesIntialPositions(const bool& noPawns){
  // initRooks();
  initPieceType<Rook>(WHITE_START_POS_ROOK);
  initPieceType<Bishop>(WHITE_START_POS_BISHOP);
  initPieceType<Queen>(WHITE_START_POS_QUEEN);
  initPieceType<King>(WHITE_START_POS_KING);
  initPieceType<Knight>(WHITE_START_POS_KNIGHT);
  if(!noPawns) initPieceType<Pawn>(WHITE_START_POS_PAWN);
}

template<class pieceType> void ChessBoard::initPieceType(std::list<Position> whiteStartingPositions){
  for(auto it = whiteStartingPositions.begin(); it != whiteStartingPositions.end();
      ++it){
    board[it->row][it->column] = new pieceType(WHITE);
    const Position blackStartPos = whiteToBlackStartPos(*it);
    board[blackStartPos.row][blackStartPos.column] = new pieceType(BLACK);
  }
}

/* Returns true if the input is of the form "A-H1-9".
  Otherwise returns false */
int ChessBoard::inputPositionIsValid(const char
                                        inputPosition[LENGTH_INPUT_STRINGS]){
  std::string invalidPositionMessage = std::string(inputPosition) +
                                      " is not on the board. Please choose a"+
                                      "position in the range A-H and 1-8";
  if(inputPosition[0] < 'A' || inputPosition[0] > 'H'){
    std::cout << invalidPositionMessage << std::endl;
    return INVALID_INPUT_POSITION;
  }
  else if(inputPosition[1] < '1' || inputPosition[1] > '8'){
    std::cout << invalidPositionMessage << std::endl;
    return INVALID_INPUT_POSITION;
  }
  return SUCCESS;
}


int ChessBoard::convertCharToPosition(const char charPosition[LENGTH_INPUT_STRINGS],
                                        Position& position){
  int errorCode = inputPositionIsValid(charPosition);
  if(errorCode) return errorCode;

  // Position in format {column, row}, {0,0} in bottom left corner of board = {A,1}
  position = {charPosition[0] - (int) 'A',  charPosition[1] - (int) '1'};
  return SUCCESS;
}

void ChessBoard::undoMove(const Position fromPosition, const Position toPosition){
  board[fromPosition.row][fromPosition.column] = board[toPosition.row][toPosition.column];
  board[toPosition.row][toPosition.column] = savedToPositions.top();
  savedToPositions.pop();
}

void ChessBoard::handleProcessCode(int processCode, Position toPosition,
                                                        Position fromPosition){
  std::string errorMessage;
  switch(processCode){
    case(NO_PIECE_IN_SQUARE): errorMessage = "No piece in square"; break;
    case(INCORRECT_PIECE_COLOUR): errorMessage = "Wrong piece colour"; break;
    case(INVALID_INPUT_POSITION): errorMessage = "Invalid input"; break;
    case(TAKING_OWN_PIECE): errorMessage = "taking own piece"; break;
    case(PIECE_IN_THE_WAY): errorMessage = "Piece in way"; break;
    case(INVALID_MOVE): errorMessage = "Invalid move"; break;
    case(MOVE_INTO_CHECK): errorMessage = "Moving into check"; break;
    default: errorMessage = "Unknown error " + std::to_string(processCode);
  }
    std::cout << "Error- " << errorMessage << std::endl;
}


/* Prints a representation of the current board state to the command line*/
std::ostream& operator<<(std::ostream & o, const ChessBoard& cb){
  Piece* pieceInSquare;
  for(int row = SIZEOFBOARD -1; row >= 0; row--){
    cb.printHorizontalLine(o);
    o << row+1 << "|";
    for(int col=0; col<SIZEOFBOARD; col++){
      pieceInSquare = cb.getPiece({col,row});
      if(pieceInSquare == nullptr) o << "  |";
      else o  << *pieceInSquare << "|";
    }
    o  << std::endl;
  }
  char colLetter = 'A';
  for(int col=0; col<SIZEOFBOARD; col++){
    o << "  " << colLetter;
    colLetter ++;
  }
  o << std::endl;
  return o;
}

void ChessBoard::printHorizontalLine(std::ostream & o){
  o << " ";
  for(int col=0; col<SIZEOFBOARD; col++){
    o <<"___";
  }
  o << std::endl;
}
