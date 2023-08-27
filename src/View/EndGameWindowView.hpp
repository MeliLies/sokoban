#ifndef __ENDGAMEWINDOWVIEW_HPP__
#define __ENDGAMEWINDOWVIEW_HPP__

#include "../utils/imports.hpp"
#include "../Subject.hpp"
#include "../Listener.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>

/**
 * The view of the window that show a game over.
 */

class EndGameWindowView : public Fl_Window,  Subject{

    Fl_Box *message = new Fl_Box(0,0,WIDTH_WINDOW,HEIGHT_WINDOW-200,"");
    Fl_Button *button = new Fl_Button(390,400,120,45,"Quit the game");

public:

    EndGameWindowView(int gameResult);
    static void pushButton(Fl_Widget* w, void* data);
    void notify(const char* var) override;
    void removeListener() override;
    void addListener(void *listener) override;
    void initMessage(int gameResult);

};

#endif