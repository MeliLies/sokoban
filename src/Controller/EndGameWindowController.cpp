#include "EndGameWindowController.hpp"

EndGameWindowController::EndGameWindowController(int gameResult){
    endGameView = new EndGameWindowView(gameResult);
    endGameView->show();
    endGameView->addListener(this); // initilize the listener from the view with itself
    Fl::run();
}


EndGameWindowController::~EndGameWindowController(){
    endGameView->removeListener();  // the listener is remove from the view since this controller will be destroy
}


/**
 * All informations the view get by the user, will be send here to the controller to handle the user action.
 * 
 * @param var const char* containing the user action. 
 */
void EndGameWindowController::handleEvent(const char* var){
    // case where the button get clicked
    if(strcmp(var,"Quit the game")==0){
        endGameView->hide();
        exit(0);
    }

    else{
        cout<<"Error label"<<endl;
    }
}