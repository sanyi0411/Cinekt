#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WinMM.Lib")
#include "objectTracking.h"

void main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "Cannot open the web cam" << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 2000);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 2000);

    cv::Mat frame;
    cap >> frame;

    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point = coord(frame);
        cv::circle(frame, point, 20, cv::Scalar(0, 0, 255), -1);
        cv::imshow("R", frame);

        if (point.x < width * 0.25 && point.y < height * 0.25) {
            std::cout << "Hello World" << std::endl;
        }

        cv::waitKey(16);
    }
}