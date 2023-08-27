#include "GameView.hpp"

GameView::GameView(vector<vector<int>> board, const char* limitSteps, const char* bestScore) : Fl_Window(300, 100, GAME_WIDTH_WINDOW, GAME_HEIGHT_WINDOW, "Game"), board{board}{
    initAllLabels(limitSteps, bestScore);
    Fl::add_timeout(1.0 / 60, Timer_CB, this);
    resizable(this);
}
/**
 * Methode that set and add messages information on the game window.
 * @param limitSteps const char* containing the limit step text.
 * @param bestScore const char* containing the best score text.
*/
void GameView::initAllLabels(const char* limitSteps, const char* bestScore){
    this->add(stepNumberLabel);
    this->add(mess);
    this->add(pressKeyMess);
    this->add(limitStepLabel);
    this->add(bestScoreLabel);

    pressKeyMess->labelsize(15);
    limitStepLabel->labelsize(25);
    limitStepLabel->label(limitSteps);
    mess->labelsize(25);
    stepNumberLabel->labelsize(25);
    bestScoreLabel->labelsize(25);

    // case when there isn't already a high score
    if(strcmp(bestScore,"0")!=0){
        bestScoreLabel->label(bestScore);
    }
}

/**
 * Methode that draws the board with the differents elements.
 */
void GameView::draw(){
    Fl_Window::draw();
    cells.clear();
    int x = 70;
    int y = 300;
    Fl_Color color;
    for (int i = 0; i < (int)board.size(); i ++){
        for(int j = 0; j < (int)board[0].size(); j++){
            switch ((int)board[i][j]) {
            case Empty:
                color = FL_WHITE;
                break;

            case Wall:
                color = FL_GRAY;
                break;
           
            case Crate:
                color = FL_RED;
                break;

            case Target:
                color = FL_GREEN;
                break;

            case Player:
                color = FL_BLUE;
                break;

            case CrateOnTarget:
                color = FL_YELLOW;
                break;
            case PlayerOnTarget:
                color = FL_BLACK;
                break;
            case LightCrate:
                color = FL_MAGENTA;
                break;
            case LightCrateOnTarget:
                color = FL_YELLOW;
                break;
            case Teleporter:
                color = FL_CYAN;
                break;
            default:
                color = FL_WHITE;
                break;
            }
            cells.push_back({{y, x}, WIDTH_BOX, HEIGHT_BOX, color});
            y += 70;
        }
        y = 300;
        x += 70;   
    }
    for(auto cell:cells){cell.draw();
    }
}

/**
 * Methode that updates the step number text on the window.
 * @param value const char* represent the text of step number.
*/
void GameView::updateStepNumber(const char* value){
    stepNumberLabel->label(value);
}

/**
 * Methode that resets the best score text.
*/
void GameView::resetBestScore(){
    bestScoreLabel->label("");
}

/**
 * Methode to handle the keyboard, then call notify() regarding the user action.
 * @param event int represents the key push event.
*/
int GameView::handle(int event) {
    if (event == FL_KEYDOWN) {

      switch (Fl::event_key()) {

        case FL_Right:
            notify("right");
            break;
        case FL_Left:
            notify("left");
            break;
        case FL_Up:
            notify("up");
            break;
        case FL_Down:
            notify("down");
            break;
        case 'r':
            notify("restart");
            break;
        case 'b':
            notify("reset");
            break;
        default: {
          // nothing to do
        }
      }
    }

    return 0;
}

/**
 * Methode that adds an observer.
 * @param listener void* is the observer.
*/
void GameView::addListener(void* listener){
    Listener* l = (Listener*) listener;
    lg=l;
}

/**
 * Methode that deletes an observer.
*/
void GameView::removeListener(){
    listeners.pop_back();
}

/**
 * Methode that notifies controller wich key is pressed.
 * @param key const char* contains text that represents wich key is pressed.
*/
void GameView::notify(const char* key){
    lg->handleEvent(key);
}

/**
 * Methode that refreshes the window image.
 * @param userdata void* is the window data.
*/
void GameView::Timer_CB(void *userdata) {
    GameView *o = static_cast<GameView *>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
}
