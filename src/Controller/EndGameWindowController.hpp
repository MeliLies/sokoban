#ifndef __ENDGAMEWINDOWCONTROLLER_HPP__
#define __ENDGAMEWINDOWCONTROLLER_HPP__

#include "../utils/imports.hpp"
#include "../Listener.hpp"
#include "../View/EndGameWindowView.hpp"

/**
 * The controller of the window that show a game over.
 */
class EndGameWindowController : public Listener{

    EndGameWindowView *endGameView;

public:

    EndGameWindowController(int gameResult);
    ~EndGameWindowController();
    void handleEvent(const char* var) override;

};


#endif