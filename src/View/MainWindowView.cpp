#include "MainWindowView.hpp"

MainWindowView :: MainWindowView(): Fl_Window(500, 200, WIDTH_WINDOW, HEIGHT_WINDOW, "Menu") {
    initButtons();
}

/**
 * Methode that add buttons on the window and sets the push action.
*/
void MainWindowView::initButtons(){
    this->add(button1);
    this->add(button2);
    this->add(button3);

    button1->when(FL_WHEN_CHANGED);
    button1->callback(pushButton,this);

    button2->when(FL_WHEN_CHANGED);
    button2->callback(pushButton,this);

    button3->when(FL_WHEN_CHANGED);
    button3->callback(pushButton, this);
}

/**
 * Methode that adds an observer.
 * @param listener void* is the observer.
*/
void MainWindowView:: addListener(void *listener){
    Listener* l = (Listener*) listener;
    listeners.push_back(l);
}

/**
 * Methode that deletes an observer.
*/
void MainWindowView::removeListener(){
    listeners.pop_back();
}

/**
 * Methode that notifies controller wich button is pressed.
 * @param buttonLabel const char* contains text that represents wich button is pushed.
*/
void MainWindowView::notify(const char *buttonLabel){
    listeners[0]->handleEvent(buttonLabel);
}

/**
 * Methode that calls the notify window with the button label that was pushed.
* @param w Fl_Widget* represents the button.
 * @param data void* represents the data of the window.
*/
void MainWindowView :: pushButton(Fl_Widget* w, void * data){
    MainWindowView *mwv = static_cast <MainWindowView*>(data); 
    if (((Fl_Button*)w)->value()){
        mwv->notify(w->label());
    }
}

/**
 * Methode that draws the window.
*/
void MainWindowView :: draw(){
    Fl_Window :: draw();
}
