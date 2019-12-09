#ifndef POSITION_H
#define POSITION_H

#include<ostream>

struct Position{
  int column;
  int row;

  /* Defintion of - operator. Subtraction done indpendently on column and row */
  Position operator-(const Position& otherPosition);

  /* Returns true of the column and row value of two positions are equal.
    False otherwise */
  bool operator==(const Position& otherPosition) const;

  /* Returns true if column or row values of two positions are not equal.
    False otherwise */
  bool operator!=(const Position& otherPosition) const;

  /* Returns ostream rep of position -> row, column */
  friend std::ostream& operator<<(std::ostream & o, const Position& p);

};



#endif
