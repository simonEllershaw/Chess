#include "Player.hpp"
#include "MoveVector.hpp"
#include <iostream>
#include <list>

Player::Player(Position kingsPosition, Colour colour, Player* opponent):
  kingsPosition(kingsPosition), colour(colour), opponent(opponent) {
    checkStatus = false;
  };

Player* Player::getOpponent() const{
  return opponent;
}

Colour Player::getColour() const{
  return colour;
}

void Player::reset(){
  if(colour == WHITE) kingsPosition = WHITE_START_POS_KING.front();
  else kingsPosition = whiteToBlackStartPos(WHITE_START_POS_KING.front());
  checkStatus = false;
}

void Player::setCheck(const bool& checkStatus){
  this->checkStatus = checkStatus;
}

void Player::setOpponent(Player* opponent){
  this->opponent = opponent;
}

void Player::setKingPosition(Position& kingsPosition){
  this->kingsPosition = kingsPosition;
}

Position Player::getKingsPosition(const ChessBoard* board){
  updateKingsPosition(board);
  return kingsPosition;
}

void Player::updateKingsPosition(const ChessBoard* board){
  Piece* possibleKing;
  // Only update position if king has moved
  possibleKing = board->getPiece(kingsPosition);
  if(possibleKing != nullptr && possibleKing->getSymbol() == SYMBOL_KING
                                    && possibleKing->getColour() == colour){
    return;
  }
// Can be improved
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      possibleKing = board->getPiece({column, row});
      if(possibleKing != nullptr && possibleKing->getSymbol() == SYMBOL_KING
                                      && possibleKing->getColour() == colour){
          kingsPosition = {column, row};
        }
    }
  }
}

bool Player::kingCanMove(ChessBoard* board){
  updateKingsPosition(board);
  return canMakeMoveFromPosition(kingsPosition, board);
}

int Player::moveIsLegal(const Position& fromPosition, const Position& toPosition,
                        ChessBoard* board){
  Piece* pieceToMove, *pieceToTake;
  int processCode;

  // Get and check moving piece
  if(fromPosition == toPosition) return INVALID_MOVE;
  pieceToMove = board->getPiece(fromPosition);
  pieceToTake = board->getPiece(toPosition);
  processCode = movingValidPiece(pieceToMove);
  if(processCode != SUCCESS) return processCode;

  const MoveVector currentMoveVector(fromPosition, toPosition);

  if(!pieceToMove->moveShapeIsValid(currentMoveVector, pieceToTake)){
    return INVALID_MOVE;
  }
  if(board->pieceInTheWay(pieceToMove, fromPosition, currentMoveVector)){
    return INVALID_MOVE;
  }

  if(toPosition == opponent->getKingsPosition(board)) return TAKES_KING;

  // Get, check and remove piece if there. Taken piece pointer transfered to
  // pieceToTake
  if(pieceToTake != nullptr && pieceToTake->getColour() == colour){
    return TAKING_OWN_PIECE;
  }
  return SUCCESS;
}

int Player::makeMove(const Position& fromPosition, const Position& toPosition,
                    ChessBoard* board){
  int processCode;

  processCode = moveIsLegal(fromPosition, toPosition, board);
  if(processCode!=SUCCESS) return processCode;

  board->movePiece(fromPosition, toPosition);

  // Check for checkmate before current player check, as can move into check if
  // it results in a checkmate. Also updates oppenets check status
  // if(opponent->inCheckmate()) return CHECKMATE;

  // If move results in player being in check undo move
  if(inCheck(board)!=NOT_IN_CHECK){
    board->undoMove(fromPosition, toPosition);
    opponent->setCheck(false);
    // King may have backtracked so check king position
    updateKingsPosition(board);
    return MOVE_INTO_CHECK;
  }

  // if(opponent->inStalemate(board)) return STALEMATE;

  return SUCCESS;
}

int Player::movingValidPiece(Piece* pieceToMove){
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
  int test;
  getKingsPosition(board);

  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      testPiece = board->getPiece({column, row});
      if(testPiece != nullptr && testPiece->getColour()!=colour){
        test = opponent->makeMove({column, row}, kingsPosition, board);
        if(test == TAKES_KING){
          return {column, row};
        }
      }
    }
  }
  return NOT_IN_CHECK;
}

bool Player::inCheckmate(ChessBoard* board){
  // Checkmate if in check, king cannot move and attacking piece cannot be
  // legally taken or blocked from the king
  if(!kingCanMove(board) && !stopAttacksOnKing(board)) return true;
  else return false;
}

bool Player::stopAttacksOnKing(ChessBoard* board){
  bool canStop = true;
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

bool Player::canTakeOrBlockPathToKing(Position& positionAttackingKing, ChessBoard* board){
  Piece* attackingPiece = board->getPiece(positionAttackingKing);
  MoveVector attackVector(positionAttackingKing, getKingsPosition(board));
  std::list<Position> positionsToGetTo
                    = attackingPiece->getPositionsVistedByMove(positionAttackingKing, attackVector);
  positionsToGetTo.push_back(positionAttackingKing);
  for(auto it = positionsToGetTo.begin(); it != positionsToGetTo.end(); ++it){
    if(canMakeMoveToPosition(*it, board)) return true;
  }
  return false;
}

bool Player::inStalemate(ChessBoard* board){
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      if(canMakeMoveFromPosition({column, row}, board)) return false;
    }
  }
  return true;
}

bool Player::canMakeMoveFromPosition(const Position fromPosition, ChessBoard* board){
  int processCode;
  for(int row = 0; row < SIZEOFBOARD; row++){
    for(int column = 0; column < SIZEOFBOARD; column++){
      processCode = makeMove(fromPosition, {column,row}, board);
      if(processCode == SUCCESS){
        board->undoMove(fromPosition, {column, row});
        return true;
      }
    }
  }
  return false;
}

bool Player::canMakeMoveToPosition(const Position toPosition, ChessBoard* board){
  int processCode;
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
