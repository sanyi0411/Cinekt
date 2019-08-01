#pragma once

#include <iostream>
#include "objectTracking.h"
#include "opencv2/core.hpp"
#include <vector>


class Invasion
{
public:
    Invasion(cv::VideoCapture cap);
    ~Invasion();

    void creatGameTable(std::vector<std::vector<int>> *gameTable);
    void creatBoxes(cv::Point point);

private:
    cv::VideoCapture _cap;
    int _width;
    int _hight;

};

