#ifndef __MAINWINDOWCONTROLLER_HPP__
#define __MAINWINDOWCONTROLLER_HPP__

#include "GameController.hpp"
#include "../Listener.hpp"
#include "../View/MainWindowView.hpp"
#include "../utils/imports.hpp"
#include <Fl/Fl_Window.H>


/**
 * The controller of the window to select a level.
 */
class MainWindowController : public Listener{

    MainWindowView *mainView;

public:

    MainWindowController(); 
    ~MainWindowController();
    
    MainWindowView *getWindow(){return mainView;}
    void handleEvent(const char *buttonLabel) override;
    
};

#endif