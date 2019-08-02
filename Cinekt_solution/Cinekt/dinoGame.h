#pragma once
#include <iostream>
#include "objectTracking.h"
#include "opencv2/core.hpp"
#include <Windows.h>
#include <WinUser.h>
class DinoGame
{
public:
    DinoGame(cv::VideoCapture cap);
    void dinoGame();
private:
    cv::VideoCapture cap;
    bool _up = false;
    bool _down = false;
    bool _center = true;
    bool _upKeyHold = false;
    bool _downKeyHold = false;
    bool _bkey[2];
    double _cy;
    double _area;
    int _height;
    int _width;
    cv::Mat _mask;
};

