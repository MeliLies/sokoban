#ifndef __GAMEVIEW_HPP__
#define __GAMEVIEW_HPP__

#include "../utils/imports.hpp"
#include "../Subject.hpp"
#include "widgets/Cell.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

/**
 * The view for the game window.
 */

class GameView : public Fl_Window, Subject {

    vector<vector<int>> board;
    vector<Cell> cells;
    Listener *lg;//Pointer to the observer 
    
    //Informations message in the game windows left side
    Fl_Box *mess = new Fl_Box(0,50,200,200, "step counter : \n \n \n limit step : \n \n \n best score : ");
    Fl_Box *pressKeyMess = new Fl_Box(75,300,100,100, "press r to restart the game \n \n press b to reset the best score");
    Fl_Box *stepNumberLabel = new Fl_Box(150,20,100,100,"0");
    Fl_Box *limitStepLabel = new Fl_Box(150,100,100,100,"");
    Fl_Box *bestScoreLabel = new Fl_Box(150,180,100,100,""); 

public:

    GameView(vector<vector<int>> board,const char *limitSteps, const char* bestScore);
    void initAllLabels(const char* limitSteps, const char* bestScore);
    void draw() override;
    void updateBoard(vector<vector<int>> b){board = b;};
    int handle(int event) override;
    void notify(const char* key)override;
    void addListener(void* Listener)override;
    void removeListener() override;
    void updateStepNumber(const char* value);
    void resetBestScore();
    static void Timer_CB(void *userdata);

};

#endif