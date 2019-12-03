#include<list>
#include<iterator>
#include<iostream>
#include<string>
#include"ChessBoard.hpp"
#include"Rook.hpp"


ChessBoard::ChessBoard(){
  setPiecesIntialPositions();
  whitePlayer = {NULL, false, WHITE, &blackPlayer};
  blackPlayer = {NULL, false, BLACK, &whitePlayer};
}


void ChessBoard::resetBoard(){
  deleteAllPieces();
  setPiecesIntialPositions();
  currentPlayer = &whitePlayer;
}


void ChessBoard::submitMove(const char fromPosInput[lengthInputStrings],
                              const char toPosInput[lengthInputStrings])
{
  Position fromPosition, toPosition;
  int processCode;
  // Read in positions
  if(convertCharToPosition(fromPosInput, fromPosition)) return;
  if(convertCharToPosition(toPosInput, toPosition)) return;

  processCode = makeMove(fromPosition, toPosition);

  if(processCode != SUCCESS){
    handleProcessCode(processCode, fromPosition, toPosition);
  }
  else{
    currentPlayer = currentPlayer->opponent;
  }
}


int ChessBoard::makeMove(Position fromPosition, Position toPosition){
  Piece* pieceToMove, *pieceToTake;
  int processCode;

  // Get and check moving piece
  pieceToMove = getPiece(fromPosition);
  processCode = movingValidPiece(pieceToMove);
  if(processCode != SUCCESS) return processCode;
  if(!moveIsAllowedByPiece(pieceToMove, fromPosition, toPosition)){
    return INVALID_MOVE;
  }

  // Get, check and remove piece if there. Taken piece pointer transfered to
  // pieceToTake
  pieceToTake = getPiece(toPosition);
  if(pieceToTake!=nullptr){
    processCode = takePiece(toPosition, pieceToTake);
    if(processCode != SUCCESS) return processCode;
  }

  movePiece(fromPosition, toPosition);

  // Check for checkmate before current player check, as can move into check if
  // it results in a checkmate. Also updates oppenets check status
  if(playerIsInCheckmate(currentPlayer->opponent)) return CHECKMATE;

  // If move results in player being in check undo move
  if(playerIsInCheck(currentPlayer)){
    undoMove(toPosition, fromPosition, pieceToTake, currentPlayer->opponent);
    return MOVE_INTO_CHECK;
  }

  if(playerIsInStalemate(currentPlayer->opponent)) return STALEMATE;

  return SUCCESS;
}



bool ChessBoard::playerIsInCheck(Player* player){
  return false;
}

bool ChessBoard::playerIsInCheckmate(Player* player){
  if(!playerIsInCheck(player)) return false;
  return false;
}

bool ChessBoard::playerIsInStalemate(Player* player){
  return false;
}


void ChessBoard::undoMove(const Position toPosition, const Position fromPosition,
                          Piece* takenPiece, Player* opponent){
  // Move piece back
  movePiece(toPosition, fromPosition);
  // Replace taken piece
  board[toPosition.row][toPosition.column] = takenPiece;
  takenPiece = nullptr;
  // Oppenent's check status must have been false at start of move
  opponent->inCheck = false;
}


int ChessBoard::movingValidPiece(Piece* pieceToMove){
  if(pieceToMove == nullptr){
    return NO_PIECE_IN_SQUARE;
  }
  else if(pieceToMove->getColour() != currentPlayer->colour){
    return INCORRECT_PIECE_COLOUR;
  }
  return SUCCESS;
}

bool ChessBoard::moveIsAllowedByPiece(Piece* pieceToMove, Position fromPosition,
                                                          Position toPosition){
  double magnitude;
  Vector normalVector;
  fromPosition.getNormAndMagToPos(toPosition, normalVector, magnitude);
  std::cout << magnitude << normalVector.column <<normalVector.row << std::endl;
  // Both cases end in same error message hence bool not int return type
  // if(!pieceToMove->moveShapeIsValid(fromPosition, toPosition)) return false;
  // if(pieceInTheWay(pieceToMove, fromPosition, toPosition)) return false;
  return true;
}

bool ChessBoard::pieceInTheWay(Piece* pieceToMove, Position fromPosition,
                                                          Position toPosition){
  // If square that needs to be moved through is occupied by a piece return true
  // Else false.
  std::list<Position> positionsToMoveThrough = pieceToMove
                        ->getSquaresBetween2Positions(fromPosition, toPosition);


  for(auto it = positionsToMoveThrough.begin(); it != positionsToMoveThrough.end();
      ++it)
  {
    std::cout<< it->column << it->row << std::endl;
    if(getPiece(*it) != nullptr) return true;
  }
  return false;
}

Piece* ChessBoard::getPiece(Position piecePosition) const{
  return board[piecePosition.row][piecePosition.column];
}


int ChessBoard::takePiece(Position piecePosition, Piece* pieceToTake){
  // First check taking a piece of a different colour
  if(pieceToTake->getColour() == currentPlayer->colour) return TAKING_OWN_PIECE;
  board[piecePosition.row][piecePosition.column] = nullptr;
  return SUCCESS;
}


void ChessBoard::movePiece(Position fromPosition, Position toPosition){
  board[toPosition.row][toPosition.column] =
                                  board[fromPosition.row][fromPosition.column];
  board[fromPosition.row][fromPosition.column] = nullptr;
}


ChessBoard::~ChessBoard(){
  deleteAllPieces();
}


void ChessBoard::deleteAllPieces(){
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(board[row][column]!=nullptr) delete board[row][column];
    }
  }
}


/* Places pieces in their intial position on the board */
void ChessBoard::setPiecesIntialPositions(){
  initRooks();
}

void ChessBoard::initRooks(){
  for(auto it = WHITE_START_POS_ROOK.begin(); it != WHITE_START_POS_ROOK.end();
      ++it){
    board[it->row][it->column] = new Rook(WHITE);
    Position blackStartPos = convertWhiteToBlackStartPos(*it);
    board[blackStartPos.row][blackStartPos.column] = new Rook(BLACK);
  }
}

Position ChessBoard::convertWhiteToBlackStartPos(const Position&
                                                          whiteStartPosition){
  // Black start positions are a reflection of white start positions around
  // board mid point: (midpoint - whitePos) + midpoint = SIZEOFBOARD - whitePos
  // -1 is required as 0 indexed
  return {whiteStartPosition.column, SIZEOFBOARD - whiteStartPosition.row - 1};
}

/* Returns true if the input is of the form "A-H1-9".
  Otherwise returns false */
int ChessBoard::inputPositionIsValid(const char
                                        inputPosition[lengthInputStrings]){
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


int ChessBoard::convertCharToPosition(const char charPosition[lengthInputStrings],
                                        Position& position){
  int errorCode = inputPositionIsValid(charPosition);
  if(errorCode) return errorCode;

  // Position in format {column, row}, {0,0} in bottom left corner of board = {A,1}
  position = {charPosition[0] - (int) 'A',  charPosition[1] - (int) '1'};
  std::cout << position.column << position.row << std::endl;

  return SUCCESS;
}

void ChessBoard::handleProcessCode(int processCode, Position toPosition,
                                                        Position fromPosition){
  std::cout<< "Error stuff " << processCode << std::endl;
}


/* Prints a representation of the current board state to the command line*/
std::ostream& operator<<(std::ostream & o, const ChessBoard& cb){
  Piece* pieceInSquare;
  for(int row = SIZEOFBOARD -1; row >= 0; row--){
    cb.printHorizontalLine();
    std::cout<< row+1 << "|";
    for(int col=0; col<SIZEOFBOARD; col++){
      pieceInSquare = cb.getPiece({col,row});
      if(pieceInSquare == nullptr) std::cout << "  |";
      else std::cout << *pieceInSquare << "|";
    }
    std::cout << std::endl;
  }
  char colLetter = 'A';
  for(int col=0; col<SIZEOFBOARD; col++){
    std::cout << "  " << colLetter;
    colLetter ++;
  }
  std::cout << std::endl;
}

void ChessBoard::printHorizontalLine(){
  std::cout<<" ";
  for(int col=0; col<SIZEOFBOARD; col++){
    std::cout<<"___";
  }
  std::cout<< std::endl;
}
