#include "MainWindowController.hpp"

MainWindowController ::MainWindowController(){
    mainView = new MainWindowView();
    mainView->addListener(this);
    mainView->show();
    Fl::run();
}


MainWindowController :: ~MainWindowController(){
    mainView->removeListener(); // remove the listener since the controller is destroyed.
}

/**
 * All informations the view get by the user, will be send here to the controller to handle the user action.
 * Here it get wich level the user wants to play with the button display on the view.
 * 
 * @param buttonLabel const char* containing the text of the button clicked. 
 */
void MainWindowController::handleEvent(const char *buttonLabel) {
    if(strcmp(buttonLabel,"Level1") == 0){
        mainView->hide();
        new GameController("resource/boards/board1.txt","resource/boards/bestScore/bestScoreBoard1.txt");
    }
    else if (strcmp(buttonLabel,"Level2") == 0){
        mainView->hide();
        new GameController("resource/boards/board2.txt","resource/boards/bestScore/bestScoreBoard2.txt");
    }
    else if (strcmp(buttonLabel,"Level3") == 0){
        mainView->hide();
        new GameController("resource/boards/board3.txt","resource/boards/bestScore/bestScoreBoard3.txt");
    }
    else{
        cout<<"Error wrong button label !\n";
    }
} 