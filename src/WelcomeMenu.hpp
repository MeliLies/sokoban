#ifndef __WELCOMEMENU_HPP__
#define __WELCOMEMENU_HPP__

#include "utils/imports.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

/**
 * The welcome window.
*/
class welcomeMenu : public Fl_Window{
    Fl_Box *welcomeLabel = new Fl_Box(400,300,100,100, "Welcome ! \n Liesenborghs Amélie & Liesenborghs Julien");
public:
    welcomeMenu();
};


welcomeMenu::welcomeMenu() : Fl_Window(500, 200, WIDTH_WINDOW, HEIGHT_WINDOW, "Welcome") {
    this->add(welcomeLabel);
    welcomeLabel->labelsize(30);
}

#endif