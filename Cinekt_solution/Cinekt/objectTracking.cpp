#include "objectTracking.h"

ColorParameters player1 = { 0,46,121,231,115,194 };
ColorParameters player2 = { 112,145,94,178,53,106 };

cv::Point coord(cv::Mat frame, ColorParameters color)
{
    int posX = 400;
    int posY = 400;

    cv::Mat imgHSV;
    cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV);

    cv::Mat imgThresholded;
    inRange(imgHSV, cv::Scalar(color.hueLow, color.saturationeLow, color.valueLow), cv::Scalar(color.hueHigh, color.saturationeHigh, color.valueHigh), imgThresholded);

    //morphological opening (removes small objects from the foreground)
    erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    //morphological closing (removes small holes from the foreground)
    dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
    erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

    //Calculate the moments of the thresholded image
    cv::Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
    if (dArea > 25000) {
        //calculate the position of the ball
        posX = dM10 / dArea;
        posY = dM01 / dArea;
    }
    return cv::Point(posX, posY);
}