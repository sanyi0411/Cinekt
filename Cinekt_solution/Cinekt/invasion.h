#pragma once

#include <iostream>
#include "objectTracking.h"
#include "opencv2/core.hpp"
#include <vector>

enum boxTypes {
    VOID,
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

    std::vector<std::vector<boxTypes>> createStartTable();

    cv::Mat creatGameTable(std::vector<std::vector<boxTypes>> &gameTable);
    void creatBoxes(cv::Point point, int boxType);

private:
    cv::VideoCapture _cap;
    int _width;
    int _hight;
    
};

