#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WinMM.Lib")
#include "objectTracking.h"
#include "invasion.h"

void main()
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "Cannot open the web cam" << std::endl;
        return;
    }

    /*cap.set(cv::CAP_PROP_FRAME_WIDTH, 2000);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 2000);

    cv::Mat frame;
    cap >> frame;

    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point1 = coord(frame, palyer1);
        cv::Point point2 = coord(frame, palyer2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
        cv::imshow("R", frame);

        if (point1.x < width * 0.25 && point1.y < height * 0.25) {
            std::cout << "Hello World" << std::endl;
        }

        cv::waitKey(16);
    }*/
    /*
    Invasion inv(cap);
    std::vector<std::vector<boxTypes>> box = inv.createStartTable();
    cv::Mat show;
    show = inv.creatGameTable(box);
    cv::imshow("show", show);
    cv::waitKey(0);*/


}