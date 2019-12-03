#include "Test.hpp"
#include "ChessBoard.hpp"
#include<iostream>

int main(){
  ChessBoard test;
  std::cout<< test << std::endl;

  std::cout<< "Take own piece" << std::endl;
  test.submitMove("A1", "C3");
  std::cout<< test << std::endl;

  std::cout<< "Take own piece" << std::endl;
  test.submitMove("H8", "E5");
  std::cout<< test << std::endl;

  std::cout<< "Take own piece" << std::endl;
  test.submitMove("H1", "A5");
  std::cout<< test << std::endl;




  return 0;
}
