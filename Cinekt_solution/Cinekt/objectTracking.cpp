#include "objectTracking.h"

ColorParameters player1 = { 255,179,156,226,97,255 };
ColorParameters player2 = { 255,179,150,252,149,255 };

cv::Point coord(cv::Mat frame, ColorParameters color)
{
    int posX = 400;
    int posY = 400;

    // Increase contrast
    cv::Mat temp;
    frame.convertTo(temp, CV_32FC3);
    cv::Mat result = (temp - cv::Scalar(128, 128, 128)) * 2 + cv::Scalar(128, 128, 128);
    result.convertTo(result, CV_8UC3);

    cv::Mat imgHSV;
    cvtColor(result, imgHSV, cv::COLOR_BGR2HSV);

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

void calibrateColors(int event, int x, int y, int flags, void *userdata)
{
    if (flags & cv::MouseEventFlags::EVENT_FLAG_LBUTTON) {
        double minHue;
        double maxHue;
        double minSat;
        double maxSat;
        double minVal;
        double maxVal;

        cv::Mat img = *((cv::Mat *)userdata);
        cv::Mat hsv;

        // Convert to HSV color space
        cvtColor(img, hsv, cv::COLOR_BGR2HSV);

        // Get click area
        cv::Rect rect(x - 10, y - 10, 20, 20);
        cv::Mat window(hsv, rect);

        // Split channels
        cv::Mat hsv_channels[3];
        cv::split(window, hsv_channels);
        cv::minMaxLoc(hsv_channels[0], &minHue, &maxHue);
        cv::minMaxLoc(hsv_channels[1], &minSat, &maxSat);
        cv::minMaxLoc(hsv_channels[2], &minVal, &maxVal);

        if (!player2Config) {
            player1 = { (int)maxHue - 20, (int)maxHue,
                (int)minSat, 255,
                (int)minVal, 255 };
            std::cout << "red: " << maxHue - 20 << " " << maxHue << " " << minSat << " " << maxSat << " " << minVal << " " << maxVal << std::endl;
            player2Config = true;
        } else {
            player2 = { (int)minHue - 20, (int)maxHue,
                (int)minSat, 255,
                (int)minVal, 255 };
            std::cout << "blue: " << maxHue - 20 << " " << maxHue << " " << minSat << " " << maxSat << " " << minVal << " " << maxVal << std::endl;
            player2Config = false;
        }
    }
}