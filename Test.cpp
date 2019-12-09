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

  std::cout<< "--------------------Test 8 Stalemate------------------" << std::endl;
  testStalemate(cb);

  std::cout<< "--------------------Test 8 Checkmate------------------" << std::endl;
  testCheckmate(cb);

  std::cout<< "--------------------Test 8 Input------------------" << std::endl;
  testInput(cb);

  std::cout<< "----------------Test 9 Sample games---------------" << std::endl;
  test10MoveCheckmate(cb);
  std::cout << cb << std::endl;

  testShortGame(cb);
  std::cout << cb << std::endl;

  testKeresVArlamowski(cb);
  std::cout << cb << std::endl;

  return 0;
}

void testCastle(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Castle Move Up -> success" << std::endl;
  cb.submitMove("A1", "A5");
  std::cout << std::endl;


  std::cout<< "Castle Move Down -> success" << std::endl;
  cb.submitMove("H8", "H5");
  std::cout << std::endl;

  std::cout<< "Castle Move Right -> success" << std::endl;
  cb.submitMove("A5", "C5");
  std::cout << std::endl;

  std::cout<< "Castle Move Left -> success" << std::endl;
  cb.submitMove("H5", "F5");
  std::cout << std::endl;

  std::cout<< "Castle diagonal move - fail" << std::endl;
  cb.submitMove("C5", "D4");
  std::cout << std::endl;

  std::cout<< "Castle non straight move - fail" << std::endl;
  cb.submitMove("C5", "E4");
  std::cout << std::endl;

}

void testKnight(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Knight Up Left Long -> success" << std::endl;
  cb.submitMove("B1", "A3");
  std::cout << std::endl;

  std::cout<< "Knight Down Right Long -> success" << std::endl;
  cb.submitMove("B8", "C6");
  std::cout << std::endl;

  std::cout<< "Knight Up Right Flat -> success" << std::endl;
  cb.submitMove("A3", "C4");
  std::cout << std::endl;

  std::cout<< "Knight Down Left Flat -> success" << std::endl;
  cb.submitMove("C6", "A5");
  std::cout << std::endl;

  std::cout<< "Knight Can Jump Pieces -> success" << std::endl;
  cb.submitMove("A1", "A3");
  cb.submitMove("A5", "B3");
  std::cout << std::endl;

  std::cout<< "Knight Straight Move -> fail" << std::endl;
  cb.submitMove("C4", "C7");
  std::cout << std::endl;
}

void testBishop(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Bishop Up Left -> success" << std::endl;
  cb.submitMove("C1", "B2");
  std::cout << std::endl;

  std::cout<< "Bishop Down Left -> success" << std::endl;
  cb.submitMove("C8", "B7");
  std::cout << std::endl;

  std::cout<< "Bishop Up Right -> success" << std::endl;
  cb.submitMove("F1", "G2");
  std::cout << std::endl;

  std::cout<< "Bishop Down Right -> success" << std::endl;
  cb.submitMove("F8", "G7");
  std::cout << std::endl;

  std::cout<< "Bishop Down -> fail" << std::endl;
  cb.submitMove("B2", "B3");
  std::cout << std::endl;

  std::cout<< "Bishop Non Straight -> fail" << std::endl;
  cb.submitMove("B2", "C6");
  std::cout << std::endl;
}

void testQueen(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Queen Diagonal -> success" << std::endl;
  cb.submitMove("D1", "B3");
  std::cout << std::endl;

  std::cout<< "Queen Straight -> success" << std::endl;
  cb.submitMove("D8", "D3");
  std::cout << std::endl;

  std::cout<< "Queen Non Straight -> fail" << std::endl;
  cb.submitMove("B3", "C5");
  std::cout << std::endl;
}

void testKing(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "King Diagonal -> success" << std::endl;
  cb.submitMove("E1", "F2");
  std::cout << std::endl;

  std::cout<< "King Straight -> success" << std::endl;
  cb.submitMove("E8", "E7");
  std::cout << std::endl;

  std::cout<< "King Horizontal -> success" << std::endl;
  cb.submitMove("F2", "G2");
  std::cout << std::endl;

  std::cout<< "King Non Straight -> fail" << std::endl;
  cb.submitMove("E7", "C6");
  std::cout << std::endl;

  std::cout<< "King move more 1 square -> fail" << std::endl;
  cb.submitMove("E7", "E5");
  std::cout << std::endl;

  cb.resetBoard();
}

void testPawn(ChessBoard& cb){
  cb.resetBoard();

  std::cout<< "Pawn Forward 1 -> success" << std::endl;
  cb.submitMove("A2", "A3");
  std::cout << std::endl;

  std::cout<< "Pawn Forward 2 -> success" << std::endl;
  cb.submitMove("B7", "B5");
  std::cout << std::endl;

  std::cout<< "Pawn Take diagonal -> success" << std::endl;
  cb.submitMove("A3", "A4");
  cb.submitMove("B5", "A4");
  std::cout << std::endl;

  std::cout<< "Pawn take vertically -> fail" << std::endl;
  cb.submitMove("A1", "A3");
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
  cb.submitMove("H5", "H3");
  std::cout << std::endl;

  std::cout<< "Pawn blocked for 2 square start -> fail" << std::endl;
  cb.submitMove("G8", "F6");
  cb.submitMove("B2", "B3");
  cb.submitMove("F7", "F5");
  std::cout<< std::endl;
}

void testMovementMechanics(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);
  std::cout << std::endl;

  std::cout<< "No Piece In Square -> fail" << std::endl;
  cb.submitMove("C4", "C5");
  std::cout << std::endl;

  std::cout<< "Move opponent's piece -> fail" << std::endl;
  cb.submitMove("B8", "B6");
  std::cout << std::endl;

  std::cout<< "Move with piece in path -> fail" << std::endl;
  cb.submitMove("C1", "A3");
  cb.submitMove("A8", "A2");
  std::cout << std::endl;

  std::cout<< "Take own piece -> fail" << std::endl;
  cb.submitMove("A8", "B8");
  std::cout << std::endl;

  std::cout<< "Take opponent's piece -> success" << std::endl;
  cb.submitMove("A8", "A3");
  std::cout << std::endl;
}

void testCheck(ChessBoard& cb){
  cb.resetBoard(NO_PAWNS);

  std::cout<< "Dont move out of check -> fail" << std::endl;
  cb.submitMove("D1", "E2");
  cb.submitMove("A8", "A7");
  std::cout << std::endl;

  cb.resetBoard(NO_PAWNS);
  std::cout<< "Move into check -> fail" << std::endl;
  cb.submitMove("E1", "D2");
  std::cout << std::endl;
}


void testStalemate(ChessBoard& cb){
  cb.resetBoard();
  // Fastest known stalemate
  // https://www.chess.com/article/view/the-shortest-stalemate-possible
  cb.submitMove("E2", "E3");
  cb.submitMove("A7", "A5");
  cb.submitMove("D1", "H5");
  cb.submitMove("A8", "A6");
  cb.submitMove("H5", "A5");
  cb.submitMove("H7", "H5");
  cb.submitMove("H2", "H4");
  cb.submitMove("A6", "H6");
  cb.submitMove("A5", "C7");
  cb.submitMove("F7", "F6");
  cb.submitMove("C7", "D7");
  cb.submitMove("E8", "F7");
  cb.submitMove("D7", "B7");
  cb.submitMove("D7", "B7");
  cb.submitMove("D8", "D3");
  cb.submitMove("B7", "B8");
  cb.submitMove("D3", "H7");
  cb.submitMove("B8", "C8");
  cb.submitMove("F7", "G6");
  cb.submitMove("C8", "E6");

  std::cout << cb << std::endl;
}

void testCheckmate(ChessBoard& cb){
  cb.resetBoard();
  std::cout << cb << std::endl;

  // 4 move checkmate
  // https://www.chess.com/article/view/the-fastest-possible-checkmate-in-chess
  cb.submitMove("F2", "F3");
  cb.submitMove("E7", "E5");
  cb.submitMove("G2", "G4");
  cb.submitMove("D8", "H4");
  std::cout << cb << std::endl;
}

void testInput(ChessBoard& cb){
  cb.resetBoard();

  cb.submitMove("A2", "A34");
  cb.submitMove("Z2", "A34");
  cb.submitMove("A-2", "A34");
  cb.submitMove("A2", "A9");
}

void test10MoveCheckmate(ChessBoard& cb){
  cb.resetBoard();

  cb.submitMove("E2", "E4");
  cb.submitMove("E7", "E5");
  cb.submitMove("G1", "F3");
  cb.submitMove("B8", "C6");
  cb.submitMove("B1", "C3");
  cb.submitMove("G8", "F6");
  cb.submitMove("F1", "C4");
  cb.submitMove("D7", "D6");
  cb.submitMove("F3", "G5");
  cb.submitMove("C8", "G4");
  cb.submitMove("C4", "F7");
  cb.submitMove("E8", "E7");
  cb.submitMove("C3", "D5");
  cb.submitMove("F6", "D5");
  cb.submitMove("D1", "G4");
  cb.submitMove("D5", "F6");
  cb.submitMove("G4", "E6");
}

void testShortGame(ChessBoard& cb){
  cb.resetBoard();

  cb.submitMove("E2","E4");
  cb.submitMove("E7","E5");
  cb.submitMove("F1","C4");
  cb.submitMove("F8","C5");
  cb.submitMove("D1","H5");
  cb.submitMove("G8","F6");
  cb.submitMove("E2","E4");
  cb.submitMove("H5","F7");
}

void testKeresVArlamowski(ChessBoard& cb){
  cb.resetBoard();

  cb.submitMove("E2","E4");
  cb.submitMove("C7","C6");
  cb.submitMove("B1","C3");
  cb.submitMove("D7","D5");
  cb.submitMove("G1","F3");
  cb.submitMove("D5","E4");
  cb.submitMove("C3","E4");
  cb.submitMove("G8","F6");
  cb.submitMove("D1","E2");
  cb.submitMove("B8","D7");
  cb.submitMove("E4","D6");
}
