#pragma once
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

struct ColorParameters {
    int hueLow;
    int hueHigh;
    int saturationeLow;
    int saturationeHigh;
    int valueLow;
    int valueHigh;
};

static bool player2Config = false;
extern ColorParameters player1;
extern ColorParameters player2;

cv::Point coord(cv::Mat, ColorParameters color);

void calibrateColors(int event, int x, int y, int flags, void *userdata);