#include "Cell.hpp"


Cell::Cell(Point center, int w, int h, const Fl_Color color)
    : box{center, w, h, FL_BLACK, color} {}

void Cell::draw() {box.draw();}

void Cell::mouseClick(Point mouseLoc) {
  if (box.contains(mouseLoc)) {
    //changer fenetre
    cout<<"oui"<<endl;
  }
}