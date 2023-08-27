#include "EndGameWindowView.hpp"

EndGameWindowView::EndGameWindowView(int gameResult): Fl_Window(500, 200, WIDTH_WINDOW, HEIGHT_WINDOW, "Game Over") {
    initMessage(gameResult);

    this->add(button);

    button->when(FL_WHEN_CHANGED);
    button->callback(pushButton,this);
}

/**
 * Methode that adds an observer.
 * @param listener void* is the observer.
*/
void EndGameWindowView:: addListener(void *listener){
    Listener* l = (Listener*) listener;
    listeners.push_back(l);
}

/**
 * Methode that deletes an observer.
*/
void EndGameWindowView::removeListener(){
    listeners.pop_back();
}

/**
 * Methode that notifies controller when the button is pressed.
 * @param buttonLabel const char* contains the tewt of the button.
*/
void EndGameWindowView::notify(const char *buttonLabel){
    listeners[0]->handleEvent(buttonLabel);
}

/**
 * Methode that calls the notify window with the button label that was pushed.
 * @param w Fl_Widget* represents the button.
 * @param data void* represents the data of the window.
*/
void EndGameWindowView ::pushButton(Fl_Widget* w, void* data){
    EndGameWindowView *egwv = static_cast <EndGameWindowView*>(data); 
    if (((Fl_Button*)w)->value()){
        egwv->notify(w->label());
    }
}

/**
 * Methode that set the end message when the game is over.
 * @param gameResult int represents the result of the game.
*/
void EndGameWindowView::initMessage(int gameResult){
    this->add(message);
    message->labelsize(35);
    
    if(gameResult){
        message->label("You Win !");
    }
    else{
        message->label("You Lose :(");
    }
}