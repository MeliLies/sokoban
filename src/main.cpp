#include "utils/imports.hpp" 
#include "Controller/MainWindowController.hpp"
#include "WelcomeMenu.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

void hideWindow(void *p){
    Fl_Window *win = static_cast<Fl_Window*>(p);
    win->hide();
}


int main(){
    welcomeMenu *win = new welcomeMenu(); //Welcome window creation.
    win->show();
    Fl::add_timeout(2.0, hideWindow, win); //hides welcome window after 2 seconds.
    Fl::run();
    new MainWindowController(); //Menu window creation.
    return 0;
}