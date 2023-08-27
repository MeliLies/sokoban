#include "GameController.hpp"

GameController::GameController(string filename, string filenameScore) : filename{filename},filenameScore{filenameScore},
                                                                        board{make_shared<Board>(filename, filenameScore)} {
    gameView = new GameView(board->getBoard(),to_string(board->getLimitStep()).c_str(), to_string(board->getBestScore()).c_str());
    initImportantPosition();
    gameView->show();
    gameView->addListener(this);
    Fl::run();
}

GameController :: ~GameController(){
    gameView->removeListener();
}

/**
 * Methode that look into the board to save the position of the player at the start of the game and the teleporters.
 */
void GameController::initImportantPosition(){
    for(int y = 0; y < board->getSizeColumn();y++){
        for(int x = 0; x < board->getSizeRow();x++){

            if(board->getBoard()[y][x] == Player){
                playerPosition.x = x;
                playerPosition.y = y;
            }

            else if(board->getBoard()[y][x] == Teleporter){
                // check if one teleporter hasn't been already save
                if (teleporter1.x == -1){
                    teleporter1.x = x;
                    teleporter1.y = y;
                }
                else{
                    teleporter2.x = x;
                    teleporter2.y = y;
                }
            }
        }
    }
}

/**
 * All informations the view get by the user, will be send here to the controller to handle the user action.
 * 
 * @param key const char* containing the key the user had pushed. 
 */
void GameController::handleEvent(const char* key){

    if(strcmp("right",key)==0){
        mouvementManager({1,0});
    }

    else if(strcmp("left",key)==0){
        mouvementManager({-1,0});
    }

    else if(strcmp("up",key)==0){ 
        mouvementManager({0,-1});
    }

    else if(strcmp("down",key)==0){   
        mouvementManager({0,1});
    }

    else if(strcmp("restart",key)==0){
        gameView->hide();
        new GameController(filename, filenameScore);
    }
    else if(strcmp("reset", key)==0){
        board->setBestScore(0);
        gameView->resetBestScore();
    }

    else{
        cout<<"Error key"<<endl;
    } 

    gameView->updateStepNumber(to_string(stepNumber).c_str()); // refresh the step counter on the view  
    checkGameState(); // check if the user win or lose everytime the user press a key.
    
}

/**
 * Methode that check the board to see if the user is in the case when the game is over (win or lose) 
 * otherwise it does nothing and the user can continue playing.
 */
void GameController::checkGameState(){

    if(board->verifyWin()){
        if(board->getBestScore() > stepNumber || board->getBestScore()==0){
            board->setBestScore(stepNumber);
        }
        gameView->hide();
        gameView->removeListener();
        new EndGameWindowController(1);
    }

    else if(board->verifyLose(stepNumber)){
        gameView->hide();
        gameView->removeListener();
        new EndGameWindowController(0);
    }
}

/**
 * Methode to check on what type of box the user try to made a mouvement, then it leads to specifics 
 * methode for every different types of box.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::mouvementManager(Point move){
    if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Empty){
        moveOnEmpty(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Crate){
        isCrateBlocked(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == LightCrate){
        isLightCrateBlocked(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Target){
        moveOnTarget(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == CrateOnTarget){
        moveCrateOnTarget(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == LightCrateOnTarget){
        moveLightCrateOnTarget(move);
    }
    else if(board->getBoard()[playerPosition.y + move.y][playerPosition.x + move.x] == Teleporter){
        teleport(move);
    }
}

/**
 * Methode when the user wants to make a move on an empty box.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::moveOnEmpty(Point move){
    replaceTarget(move); // check if the user, before the mouvement, was on a target box so it can replace it by a target.
    addMouvement(move);
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

/**
 * Methode that check if a crate the user wants to push isn't already blocked by a wall or another crate,
 * if it's not the case it call a methode that'll make the mouvement.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::isCrateBlocked(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty){
        moveCrate(move, Crate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target){
        moveCrate(move, CrateOnTarget);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Teleporter){
        moveCrate(move, Crate);
    }
}

/**
 * Methode that check if a light crate the user wants to push isn't already blocked by a wall,
 * if it's not the case, it will also check if the user try to push two consecutive light crate together.
 * It will call a methode to make the mouvement regarding in wich case the light crate is.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::isLightCrateBlocked(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty){
        moveLightCrate(move, LightCrate, -1);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target){
        moveLightCrate(move, LightCrateOnTarget, -1);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Teleporter){
        moveLightCrate(move, LightCrate, -1);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrate && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Empty){
        moveLightCrate(move, LightCrate, LightCrate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrate && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Target){
        moveLightCrate(move, LightCrate, LightCrateOnTarget);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrateOnTarget && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Empty){
        moveLightCrate(move, LightCrateOnTarget, LightCrate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrateOnTarget && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Target){
        moveLightCrate(move, LightCrateOnTarget, LightCrateOnTarget);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrate && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Teleporter){
        moveLightCrate(move, LightCrate, LightCrate);
    }
    else if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == LightCrateOnTarget && board->getBoard()[playerPosition.y + (move.y*3)][playerPosition.x + (move.x*3)] == Teleporter){
        moveLightCrate(move, LightCrateOnTarget, LightCrate);
    }
}

/**
 * Methode that will make the mouvement in the board when the user wants to push a crate, then call the view to update it.
 * @param move Point that contains the mouvement of the ueser.
 * @param type Int that represent the type of the box the crate will have after getting pushed depending if it's on a target or an empty box.
 */
void GameController::moveCrate(Point move, int type){
    replaceTarget(move);
    addMouvement(move);
    board->modifyBoard({playerPosition.x, playerPosition.y},{playerPosition.x + move.x, playerPosition.y + move.y},Player,type);
    if((playerPosition.x == teleporter1.x && playerPosition.y == teleporter1.y) || (playerPosition.x == teleporter2.x && playerPosition.y == teleporter2.y)){
        teleport({0,0});
    }
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

/**
 * Methode that will make the mouvement in the board when the user wants to push a light crate, then call the view to update it.
 * @param move Point that contains the mouvement
 * @param type1 Int that represent the type of the box the first light crate will have after getting pushed depending if it's 
 *              on a target or an empty box.
 * @param type2 Int same has the type1 but for the second light crate getting pushed if two light crate are next to each other
 *              when pushed.
 */
void GameController::moveLightCrate(Point move, int type1, int type2){
    replaceTarget(move);
    addMouvement(move);
    board->modifyBoard({playerPosition.x, playerPosition.y},{playerPosition.x + move.x, playerPosition.y + move.y}, Player, type1);
    if(type2 > -1){
        board->modifyBoard({playerPosition.x + move.x, playerPosition.y + move.y},{playerPosition.x + move.x*2, playerPosition.y + move.y*2},type1, type2); 
    }
    if((playerPosition.x == teleporter1.x && playerPosition.y == teleporter1.y) || (playerPosition.x == teleporter2.x && playerPosition.y == teleporter2.y)){
        teleport({0,0});
    }
    gameView->updateBoard(board->getBoard());
    gameView->draw(); 
}

/**
 * Methode when the user wants to move on a target and check every possibilities.
 * @param move Point that contains the mouvement of the user.
 */
void GameController::moveOnTarget(Point move){
    if(board->getBoard()[playerPosition.y][playerPosition.x]==PlayerOnTarget){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Target, PlayerOnTarget);
    }
    else if(board->getBoard()[teleporter1.y][teleporter1.x]==Player || board->getBoard()[teleporter2.y][teleporter2.x]==Player){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Teleporter, PlayerOnTarget);
    }
    else{
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Empty, PlayerOnTarget);    
    }
    addMouvement(move);
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

/**
 * Methode used when the user wants to push a crate on a target point.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::moveCrateOnTarget(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Empty || board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Target 
        || board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] == Teleporter){
        isCrateBlocked(move);
        moveOnTarget({0,0});
    }
}

/**
 * Methode used to move a light crate on a target point.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::moveLightCrateOnTarget(Point move){
    if(board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != Wall && board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != Crate 
        &&  board->getBoard()[playerPosition.y + (move.y*2)][playerPosition.x + (move.x*2)] != CrateOnTarget){
        isLightCrateBlocked(move);
        moveOnTarget({0,0});
    }
}

/**
 * Methode used when the player was on a target point and make a mouvement so the initial position can be replaced
 * by a target point again.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::replaceTarget(Point move){
    if(board->getBoard()[playerPosition.y][playerPosition.x]==PlayerOnTarget){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Target, Player);    
    }
    else if(board->getBoard()[teleporter1.y][teleporter1.x]==Player || board->getBoard()[teleporter2.y][teleporter2.x]==Player){
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Teleporter, Player);
    }
    else{
        board->modifyBoard(playerPosition,{playerPosition.x + move.x, playerPosition.y + move.y},Empty, Player);
    }
}

/**
 * Methode used to teleport the player and check if the teleporters aren't blocked by a crate.
 * @param move Point that contains the mouvement of the ueser.
 */
void GameController::teleport(Point move){
    replaceTarget(move);
    addMouvement(move);

    if(playerPosition.x == teleporter1.x && playerPosition.y == teleporter1.y){
        if(board->getBoard()[teleporter2.y][teleporter2.x]==Teleporter){
            playerPosition.x = teleporter2.x;
            playerPosition.y = teleporter2.y;
            board->modifyBoard({teleporter1.x, teleporter1.y},playerPosition,Teleporter, Player);
        }
    }
    else{
        if(board->getBoard()[teleporter1.y][teleporter1.x]==Teleporter){
            playerPosition.x = teleporter1.x;
            playerPosition.y = teleporter1.y;
            board->modifyBoard({teleporter2.x, teleporter2.y},playerPosition,Teleporter, Player);
        }
    }
    gameView->updateBoard(board->getBoard());
    gameView->draw();
}

/**
 * Methode used when a mouvement is valid, then increment the step counter and move the player position on the board
 * @param move Point that contains the mouvement of the ueser.
*/
void GameController::addMouvement(Point move){
    playerPosition.x += move.x;
    playerPosition.y += move.y;
    stepNumber++;
}