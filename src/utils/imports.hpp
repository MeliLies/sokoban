#ifndef __IMPORTS__HPP
#define __IMPORTS__HPP

// imports we need

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>
#include <string.h>
#include <array>
#include<unistd.h>
#include <time.h>
#include<bits/stdc++.h>

using namespace std;

struct Point {
  int x, y;
};

enum cellType{Empty, Wall, Crate, Target, Player, CrateOnTarget, PlayerOnTarget, LightCrate, LightCrateOnTarget, Teleporter};


// Global values

constexpr int HEIGHT_WINDOW = 800;
constexpr int WIDTH_WINDOW = 900;
constexpr int GAME_HEIGHT_WINDOW = 900;
constexpr int GAME_WIDTH_WINDOW = 1700;
constexpr int HEIGHT_BOX = 60;
constexpr int WIDTH_BOX = 60;

#endif