#ifndef __BOX_HPP__
#define __BOX_HPP__

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>

#include "../../utils/imports.hpp"

using namespace std;


class Box {

  Point    center;
  int      w, h;
  Fl_Color fillColor, frameColor;

 public:

  Box(Point center, int w, int h, Fl_Color frameColor,
                     Fl_Color fillColor)
    : center{center},
      w{w},
      h{h},
      fillColor{fillColor},
      frameColor{frameColor} {}
  void     draw();
  void     setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() { return fillColor; }
  void     setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() { return frameColor; }
  void     setWidth(int neww) { w = neww; }
  void     setHeight(int newh) { h = newh; }
  int      getWidth() { return w; }
  int      getHeight() { return h; }
  bool     contains(Point p);
  Point    getCenter() { return center; }
  
};

#endif