#ifndef POSITION_H
#define POSITION_H

#include<ostream>
// #include"Helper.hpp"

struct Position{
  int column;
  int row;

  void getNormAndMagToPos(Position& otherPosition, Vector& normal,
                                                  int& magnitude);

  Position operator-(Position& otherPosition);

  friend std::ostream& operator<<(std::ostream & o, Position& p);

};

#endif
