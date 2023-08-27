#include "Board.hpp"

Board::Board(string filename, string filenameScore) : filename{filename}, filenameScore{filenameScore} {
    initBoard(filename);
    initScore(filenameScore);
}


/**
 * Methode to build the board given by a file.
 * @param filename Path of a file that contains the board and the limit step of a level.
 */
void Board::initBoard(string filename) {
    string line;
    ifstream file(filename);

    getline(file,line);
    limitStep = stoi(line); // convert string into integer

    while(getline(file,line)){ // check every row (line) of the file
        vector<int> v = {};
        for(char c:line){ // check every characters of a line
            v.push_back(c - '0');
        }
        board.push_back(v);
    }
    file.close();
}

/**
 * Methode used to init the bestScore if one already get saved in the file for that.
 * @param filenameScore Path of the file that contains the high score of a level.
 */
void Board::initScore(string filenameScore){
    string line;
    ifstream file(filenameScore);
    getline(file,line);
    bestScore = stoi(line);
    file.close();
}


/**
 * Methode used when a mouvement is valid so the board need to update itself with its new state.
 * @param posInit Point that contains the position before the movement of the user.
 * @param nextPos Point that contains the position after the movement of the user.
 * @param typePosInit Integer that represent the type of the box on the position before the 
 *                    movement of the user.
 * @param typeNextPos Integer that represent the type of the box on the position after the 
 *                    movement of the user.
 */
void Board::modifyBoard(Point posInit, Point nextPos, int typePosInit, int typeNextPos){
    board[posInit.y][posInit.x] = typePosInit;
    board[nextPos.y][nextPos.x] = typeNextPos;
}


/**
 * Methode use to check if every target have a crate on them, if it's the return true.
 */
bool Board::verifyWin(){
    int x = 0;
    while(x < getSizeRow()){
        int y = 0;
        while(y < getSizeColumn()){
            if(board[y][x] == Target || board[y][x] == PlayerOnTarget){
                return false;
            }
            y++;
        }
        x++;
    }
    return true;
}


/**
 * Methode use to check if the user lose the game.
 * @param currentStep Integer that contains the number of step the user already made.
 */
bool Board::verifyLose(int currentStep){
    // case when the player exceeds the limit step for the level.
    if(currentStep==limitStep){
        return true;
    }
    return false;
}

/**
 * Methode to save a new high score in the file that matches the level played.
 * @param newBestScore Integer that conatins the new high score.
 */
void Board::saveBestScore(int newBestScore){
    ofstream out(filenameScore);
    out<<newBestScore;
    out.close();
}