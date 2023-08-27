#ifndef __CELL_HPP__
#define __CELL_HPP__

#include <iostream>

#include "Box.hpp"

using namespace std;

class Cell {

  Box box;

 public:
 
  // Constructor
  Cell(Point center, int w, int h, const Fl_Color color);

  // Methods that draw and handle events
  void  draw();
  void  mouseMove(Point /* mouseLoc */){}
  void  mouseClick(Point mouseLoc);
  Point getCenter() { return box.getCenter(); }

};

#endif