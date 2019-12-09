#include "Player.hpp"
#include "MoveVector.hpp"
#include <iostream>
#include <list>

Player::Player(Position kingsPosition, Colour colour, Player* opponent):
  kingsPosition(kingsPosition), colour(colour), opponent(opponent) {};

Player* Player::getOpponent() const{
  return opponent;
}

Colour Player::getColour() const{
  return colour;
}

void Player::reset(){
  if(colour == WHITE) kingsPosition = WHITE_START_POS_KING.front();
  else kingsPosition = whiteToBlackStartPos(WHITE_START_POS_KING.front());
}

void Player::setOpponent(Player* opponent){
  this->opponent = opponent;
}


void Player::updateKingsPosition(const ChessBoard* board){
  // Only update position if king has moved from currently recorded position
  if(isPlayersKing(board->getPiece(kingsPosition))) return;

  // Find king Can be improved
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(isPlayersKing(board->getPiece({column, row}))){
          kingsPosition = {column, row};
        }
    }
  }
}

bool Player::isPlayersKing(Piece* possibleKing){
  if(possibleKing != nullptr && possibleKing->getSymbol() == SYMBOL_KING
                                  && possibleKing->getColour() == colour){
    return true;
  }
  else return false;
}

bool Player::kingCanMove(ChessBoard* board){
  return canMakeMoveFromPosition(kingsPosition, board);
}


int Player::makeMove(const Position& fromPosition, const Position& toPosition,
                    ChessBoard* board){
  int processCode;

  processCode = moveIsLegal(fromPosition, toPosition, board);
  if(processCode!=SUCCESS) return processCode;

  board->movePiece(fromPosition, toPosition);
  updateKingsPosition(board);

  // If move results in player being in check undo move
  if(inCheck(board) != NOT_IN_CHECK){
    board->undoMove(fromPosition, toPosition);
    // King may have backtracked so check king position
    return MOVE_INTO_CHECK;
  }
  return SUCCESS;
}

int Player::moveIsLegal(const Position& fromPosition, const Position& toPosition,
                        ChessBoard* board){
  Piece* pieceToMove, *pieceToTake;
  int processCode;

  // Sanity check
  if(fromPosition == toPosition) return INVALID_MOVE;

  // Get piece involved in move
  pieceToMove = board->getPiece(fromPosition);
  pieceToTake = board->getPiece(toPosition);

  // Check moving a valid piece
  processCode = movingValidPiece(pieceToMove);
  if(processCode != SUCCESS) return processCode;

  // Check move shape is valid and no pieces in the way
  const MoveVector currentMoveVector(fromPosition, toPosition);
  if(!pieceToMove->moveShapeIsValid(currentMoveVector, pieceToTake)){
    return INVALID_MOVE;
  }
  if(board->pieceInTheWay(pieceToMove, fromPosition, currentMoveVector)){
    return INVALID_MOVE;
  }

  // Ensure not taking own piece
  if(pieceToTake != nullptr && pieceToTake->getColour() == colour){
    return TAKING_OWN_PIECE;
  }
  return SUCCESS;
}


int Player::movingValidPiece(Piece* pieceToMove) const{
  // Have to move a piece and has to be of your colour
  if(pieceToMove == nullptr){
    return NO_PIECE_IN_SQUARE;
  }
  else if(pieceToMove->getColour() != colour){
    return INCORRECT_PIECE_COLOUR;
  }
  return SUCCESS;
}


Position Player::inCheck(ChessBoard* board){
  Piece* testPiece;
  int processCode;
  // Iterate over board to find all opponent's pieces
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      testPiece = board->getPiece({column, row});
      if(testPiece != nullptr && testPiece->getColour()!=colour){
        // If opponent's piece can legally move to player's king position then
        // the player is in check
        processCode = opponent->moveIsLegal({column, row}, kingsPosition, board);
        if(processCode == SUCCESS) return {column, row};
      }
    }
  }
  // Else not in check
  return NOT_IN_CHECK;
}

bool Player::inCheckmate(ChessBoard* board){
  // Checkmate if in check, king cannot move and attacking pieces cannot be
  // legally taken or blocked from the king
  if(!kingCanMove(board) && !stopAttacksOnKing(board)) return true;
  else return false;
}

bool Player::stopAttacksOnKing(ChessBoard* board){
  bool canStop = true;
  updateKingsPosition(board);
  Position positionAttackingKing = inCheck(board);

  if(positionAttackingKing != NOT_IN_CHECK){
    if(canTakeOrBlockPathToKing(positionAttackingKing, board)){
      // Cover condition of multiple pieces attacking King
      board->takePiece(positionAttackingKing);
      canStop = stopAttacksOnKing(board);
      board->undoMove(positionAttackingKing, positionAttackingKing);
    }
    else canStop = false;
  }
  return canStop;
}

bool Player::canTakeOrBlockPathToKing(Position& positionAttackingKing,
                                                            ChessBoard* board){
  // Get a list of the position of the attacking piece and the squares vistied
  // by it to take the king.
  Piece* attackingPiece = board->getPiece(positionAttackingKing);
  MoveVector attackVector(positionAttackingKing, kingsPosition);
  std::list<Position> positionsToGetTo
                    = attackingPiece->getPositionsVistedByMove
                                          (positionAttackingKing, attackVector);
  positionsToGetTo.push_back(positionAttackingKing);

  // If Player can move a piece to any positions in this list they can block the
  // path or take the piece (i.e. get out of check)
  for(auto it = positionsToGetTo.begin(); it != positionsToGetTo.end(); ++it){
    if(canMakeMoveToPosition(*it, board)) return true;
  }
  return false;
}

bool Player::inStalemate(ChessBoard* board){
  // If no pieces on the board can move it is a stalemate
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(canMakeMoveFromPosition({column, row}, board)) return false;
      }
  }
  return true;
}

bool Player::canMakeMoveFromPosition(const Position fromPosition,
                                                            ChessBoard* board){
  int processCode;
  // Iterate over whole board and check if can move to that position
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      processCode = makeMove(fromPosition, {column,row}, board);
      if(processCode == SUCCESS){
        board->undoMove(fromPosition, {column, row});
        updateKingsPosition(board);
        return true;
      }
    }
  }
  return false;
}

bool Player::canMakeMoveToPosition(const Position& toPosition,
                                                            ChessBoard* board){
  int processCode;
  // Iterate over whole board and check if can move from that position
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      processCode = makeMove({column,row}, toPosition, board);
      if(processCode == SUCCESS){
        board->undoMove({column, row}, toPosition);
        return true;
      }
    }
  }
  return false;
}

std::ostream& operator<<(std::ostream & o, const Player& pl){
  return o << pl.getColour();
}
