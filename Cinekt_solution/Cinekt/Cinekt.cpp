#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WinMM.Lib")
#include "objectTracking.h"
#include "invasion.h"
#include "pongGame.h"

void main()
{
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cout << "Cannot open the web cam" << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    cv::Mat frame;
    cap >> frame;

    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::namedWindow("Cinekt");
    cv::setMouseCallback("Cinekt", calibrateColors, &frame);

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point1 = coord(frame, player1);
        cv::Point point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
        cv::imshow("Cinekt", frame);

        if (point1.x < width * 0.25 && point1.y < height * 0.25) {
            pongGame(cap);
        }

        if (point1.x < width * 0.25 && point1.y > height * 0.75) {
            Invasion invasion(cap);
            invasion.runGame();
        }

        int input = cv::waitKey(16);
        if (input == 32) {
            std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
            break;
        }
    }
}