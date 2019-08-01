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

extern ColorParameters palyer1;
extern ColorParameters palyer2;

cv::Point coord(cv::Mat, ColorParameters color);

