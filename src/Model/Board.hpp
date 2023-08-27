#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "../utils/imports.hpp"


/**
 * Model that represent our board we used during the game and all the important data of it (files, highscore, etc)
 */
class Board {
private:

    string filename;
    string filenameScore;
    vector<vector<int>> board;
    int bestScore;
    int limitStep;

public:
    // constructor, getters and setters
    Board(string filename, string filenameScore);
    void initBoard(string filename);
    void initScore(string filenameScore);
    int getLimitStep(){return limitStep;}
    int getBestScore(){return bestScore;}
    void setBestScore(int newBestScore){bestScore=newBestScore; saveBestScore(bestScore);}
    vector<vector<int>> getBoard(){return board;};
    int getSizeColumn(){return (int)board.size();};
    int getSizeRow(){return (int)board[0].size();};

    void modifyBoard(Point posInit, Point nextPos, int typePosInit, int typeNextPos);
    bool verifyWin();
    bool verifyLose(int currentStep);
    void saveBestScore(int newBestScore);

};

#endif