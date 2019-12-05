#include "Test.hpp"
#include<iostream>

bool NO_PAWNS = true;

int main(){
  ChessBoard cb;
  std::cout<< "---------------Test 1 Castle Movement-------------" << std::endl;
  testCastle(cb);

  std::cout<< "---------------Test 2 Knight Movement-------------" << std::endl;
  testKnight(cb);

  std::cout<< "---------------Test 3 Bishop Movement-------------" << std::endl;
  testBishop(cb);

  std::cout<< "---------------Test 4 Queen Movement--------------" << std::endl;
  testQueen(cb);

  std::cout<< "------------------Test 4 King Movement------------" << std::endl;
  testKing(cb);

  std::cout<< "----------------Test 5 Pawn Movement--------------" << std::endl;
  testPawn(cb);

  std::cout<< "--------------Test 6 Movement Mechanics-----------" << std::endl;
  testMovementMechanics(cb);

  std::cout<< "--------------------Test 7 Check------------------" << std::endl;
  testCheck(cb);

  return 0;
}

void testCastle(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Castle Move Up -> success" << std::endl;
  cb.submitMove("A1", "A5");
  std::cout<< cb << std::endl;

  std::cout<< "Castle Move Down -> success" << std::endl;
  cb.submitMove("H8", "H5");
  std::cout<< cb << std::endl;

  std::cout<< "Castle Move Right -> success" << std::endl;
  cb.submitMove("A5", "C5");
  std::cout<< cb << std::endl;

  std::cout<< "Castle Move Left -> success" << std::endl;
  cb.submitMove("H5", "F5");
  std::cout<< cb << std::endl;

  std::cout<< "Castle diagonal move - fail" << std::endl;
  cb.submitMove("C5", "D4");
  std::cout<< cb << std::endl;

  std::cout<< "Castle non straight move - fail" << std::endl;
  cb.submitMove("C5", "E4");
  std::cout<< cb << std::endl;

}

void testKnight(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Knight Up Left Long -> success" << std::endl;
  cb.submitMove("B1", "A3");
  std::cout<< cb << std::endl;

  std::cout<< "Knight Down Right Long -> success" << std::endl;
  cb.submitMove("B8", "C6");
  std::cout<< cb << std::endl;

  std::cout<< "Knight Up Right Flat -> success" << std::endl;
  cb.submitMove("A3", "C4");
  std::cout<< cb << std::endl;

  std::cout<< "Knight Down Left Flat -> success" << std::endl;
  cb.submitMove("C6", "A5");
  std::cout<< cb << std::endl;

  std::cout<< "Knight Can Jump Pieces -> success" << std::endl;
  cb.submitMove("A1", "A3");
  std::cout<< cb << std::endl;
  cb.submitMove("A5", "B3");
  std::cout<< cb << std::endl;

  std::cout<< "Knight Straight Move -> fail" << std::endl;
  cb.submitMove("C4", "C7");
  std::cout<< cb << std::endl;
}

void testBishop(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Bishop Up Left -> success" << std::endl;
  cb.submitMove("C1", "B2");
  std::cout<< cb << std::endl;

  std::cout<< "Bishop Down Left -> success" << std::endl;
  cb.submitMove("C8", "B7");
  std::cout<< cb << std::endl;

  std::cout<< "Bishop Up Right -> success" << std::endl;
  cb.submitMove("F1", "G2");
  std::cout<< cb << std::endl;

  std::cout<< "Bishop Down Right -> success" << std::endl;
  cb.submitMove("F8", "G7");
  std::cout<< cb << std::endl;

  std::cout<< "Bishop Down -> fail" << std::endl;
  cb.submitMove("B2", "B3");
  std::cout<< cb << std::endl;

  std::cout<< "Bishop Non Straight -> fail" << std::endl;
  cb.submitMove("B2", "C6");
  std::cout<< cb << std::endl;
}

void testQueen(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Queen Diagonal -> success" << std::endl;
  cb.submitMove("D1", "B3");
  std::cout<< cb << std::endl;

  std::cout<< "Queen Straight -> success" << std::endl;
  cb.submitMove("D8", "D3");
  std::cout<< cb << std::endl;

  std::cout<< "Queen Non Straight -> fail" << std::endl;
  cb.submitMove("B3", "C5");
  std::cout<< cb << std::endl;
}

void testKing(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "King Diagonal -> success" << std::endl;
  cb.submitMove("E1", "D2");
  std::cout<< cb << std::endl;

  std::cout<< "King Straight -> success" << std::endl;
  cb.submitMove("E8", "E7");
  std::cout<< cb << std::endl;

  std::cout<< "King Horizontal -> success" << std::endl;
  cb.submitMove("D2", "C3");
  std::cout<< cb << std::endl;

  std::cout<< "King Non Straight -> fail" << std::endl;
  cb.submitMove("E7", "C6");
  std::cout<< cb << std::endl;

  std::cout<< "King move more 1 square -> fail" << std::endl;
  cb.submitMove("E7", "E5");
  std::cout<< cb << std::endl;

  cb.resetBoard();
}

void testPawn(ChessBoard& cb){
  cb.resetBoard();

  std::cout<< "Pawn Forward 1 -> success" << std::endl;
  cb.submitMove("A2", "A3");
  std::cout<< cb << std::endl;

  std::cout<< "Pawn Forward 2 -> success" << std::endl;
  cb.submitMove("B7", "B5");
  std::cout<< cb << std::endl;

  std::cout<< "Pawn Take diagonal -> success" << std::endl;
  cb.submitMove("A3", "A4");
  std::cout<< cb << std::endl;
  cb.submitMove("B5", "A4");
  std::cout<< cb << std::endl;

  std::cout<< "Pawn take vertically -> fail" << std::endl;
  cb.submitMove("A1", "A3");
  std::cout<< cb << std::endl;
  cb.submitMove("A4", "A3");
  std::cout << std::endl;

  std::cout << "Pawn move diagonally without taking -> fail" << std::endl;
  cb.submitMove("A4", "B3");
  std::cout << std::endl;

  std::cout<< "Pawn take diagonally > 1 square -> fail" << std::endl;
  cb.submitMove("A4", "C2");
  std::cout << std::endl;

  std::cout<< "Pawn move backward -> fail" << std::endl;
  cb.submitMove("A4", "A5");
  std::cout << std::endl;

  std::cout<< "Pawn move horizontal -> fail" << std::endl;
  cb.submitMove("A4", "B4");
  std::cout << std::endl;

  std::cout<< "Pawn move backward -> fail" << std::endl;
  cb.submitMove("A4", "A5");
  std::cout << std::endl;

  std::cout<< "Pawn move 2 squares after 1st move -> fail" << std::endl;
  cb.submitMove("H7", "H5");
  cb.submitMove("D2", "D3");
  std::cout<< cb << std::endl;
  cb.submitMove("H5", "H3");
  std::cout<< cb << std::endl;

  std::cout<< "Pawn blocked for 2 square start -> fail" << std::endl;
  cb.submitMove("G8", "F6");
  cb.submitMove("B2", "B3");
  std::cout<< cb << std::endl;
  cb.submitMove("F7", "F5");
  std::cout<< std::endl;
}

void testMovementMechanics(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);
  std::cout<< cb << std::endl;

  std::cout<< "No Piece In Square -> fail" << std::endl;
  cb.submitMove("C4", "C5");
  std::cout << std::endl;

  std::cout<< "Move opponent's piece -> fail" << std::endl;
  cb.submitMove("B8", "B6");
  std::cout << std::endl;

  std::cout<< "Move with piece in path -> fail" << std::endl;
  cb.submitMove("C1", "A3");
  std::cout<< cb << std::endl;
  cb.submitMove("A8", "A2");
  std::cout << std::endl;

  std::cout<< "Take own piece -> fail" << std::endl;
  cb.submitMove("A8", "B8");
  std::cout << std::endl;

  std::cout<< "Take opponent's piece -> success" << std::endl;
  cb.submitMove("A8", "A3");
  std::cout << cb << std::endl;
}

void testCheck(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Dont move out of check -> fail" << std::endl;
  cb.submitMove("D1", "E2");
  std::cout << cb << std::endl;
  cb.submitMove("A8", "A7");
  std::cout << cb << std::endl;

  cb.resetBoard(NO_PAWNS);
  std::cout<< "Move into check -> fail" << std::endl;
  cb.submitMove("E1", "D2");
  std::cout << cb << std::endl;




}
