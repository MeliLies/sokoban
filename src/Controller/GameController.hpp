#include "../utils/imports.hpp"
#include "../Listener.hpp"
#include "../View/GameView.hpp"
#include "../Model/Board.hpp"
#include "EndGameWindowController.hpp"

/**
 * The controller for the game window.
 */
class GameController : public Listener {

    string filename; // file that contain the board and the limit step on each level
    string filenameScore;
    GameView *gameView;
    shared_ptr<Board> board;
    Point playerPosition;
    Point teleporter1 = {-1, -1};  // abstract value
    Point teleporter2;
    int stepNumber = 0;

public:

    GameController(string filename, string filenameScore);
    ~GameController();
    void initImportantPosition();
    void handleEvent(const char* key) override;
    void mouvementManager(Point move);
    void moveOnEmpty(Point move);
    void moveCrate(Point move, int type);
    void moveLightCrate(Point move, int type1, int type2);
    void isCrateBlocked(Point move);
    void isLightCrateBlocked(Point move);
    void moveOnTarget(Point move);
    void moveCrateOnTarget(Point move);
    void moveLightCrateOnTarget(Point move);
    void replaceTarget(Point move);
    void teleport(Point move);
    void addMouvement(Point move);
    void checkGameState();
};
