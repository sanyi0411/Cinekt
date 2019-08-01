#pragma once

#include <iostream>
#include "objectTracking.h"
#include "opencv2/core.hpp"
#include <vector>

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

    std::vector<std::vector<boxTypes>> createStartTable();

    cv::Mat creatGameTable();
    void creatBoxes(cv::Point point, int boxType);
    void creatMovedPlayer(int &x);

private:
    std::vector<std::vector<boxTypes>> _gameTable;
    cv::VideoCapture _cap;
    int _width;
    int _hight;
    
};

