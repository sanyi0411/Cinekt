#pragma once

#include <iostream>
#include "objectTracking.h"
#include "opencv2/core.hpp"
#include <vector>
#include <time.h>

#define TABLE_SIZE 19
#define RECTANGLE_PARAMETER 30
#define WINDOW_PARAMETER 540
#define AMOUNT_OF_LINE 10

enum boxTypes {
    BLANK,
    GREEN,
    YELLOW,
    RED,
    PLAYER = 9,
    PROJECTILE = -1
};


class Invasion
{
public:
    Invasion(cv::VideoCapture cap);
    ~Invasion();

    void setGameTable(std::vector<std::vector<boxTypes>> &gameTable);
    std::vector<std::vector<boxTypes>> getGameTable();
    void setPlayerX(int playerX);

    void createStartTable();

    void runGame();

    cv::Mat creatGameTable();
    void creatBoxes();
    void creatProjectile();

    void saveFirePoints(int y);
    bool fire();

    void movedPlayer(int x);
    void movedProjectile();
    void movedBoxes();
    
    void destroyProjectile();
    void destroyProjectileWithCollision(int position);
    void gameOver();
    
private:
    std::vector<std::vector<boxTypes>> _gameTable;
    cv::VideoCapture _cap;
    int _width;
    int _height;
    int _playerX = TABLE_SIZE / 2;
    std::vector<int> _fire = {0, 0};
    std::vector<std::vector<int>> _projectilePoint;
    bool _run = true;
};

