#ifndef POSITION_H
#define POSITION_H

#include<ostream>

struct Position{
  int column;
  int row;

  Position operator-(const Position& otherPosition);

  bool operator==(const Position& otherPosition) const;

  bool operator!=(const Position& otherPosition) const;

  friend std::ostream& operator<<(std::ostream & o, const Position& p);

};



#endif
