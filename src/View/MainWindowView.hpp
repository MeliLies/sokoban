#ifndef __MAINWINDOWVIEW_HPP__
#define __MAINWINDOWVIEW_HPP__

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

#include "../utils/imports.hpp"
#include "../Listener.hpp"
#include "../Subject.hpp"

/**
 * The view of the window to select a level.
 */

class MainWindowView : public Fl_Window, Subject {

    //Levels selection buttons
    Fl_Button *button1 = new Fl_Button(400,200,120,45,"Level1");
    Fl_Button *button2 = new Fl_Button(400,300,120,45,"Level2");
    Fl_Button *button3 = new Fl_Button(400,400,120,45,"Level3");

public:

    MainWindowView();
    void initButtons();
    static void pushButton(Fl_Widget* w, void* data);
    void addListener(void *listener) override;
    void removeListener() override;
    void notify(const char *buttonLabel) override;
    void draw() override;
    
};

#endif