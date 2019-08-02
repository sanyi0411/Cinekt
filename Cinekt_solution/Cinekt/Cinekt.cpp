#include <iostream>
#include <time.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WinMM.Lib")
#include "objectTracking.h"
#include "pongGame.h"
#include "guessGame.h"

void main()
{
    srand(time(NULL));
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

    const std::string welcomeText = "Welcome to Cinekt!";
    int fontFace = cv::FONT_HERSHEY_TRIPLEX;
    int fontScale = 3;
    int thickness = 5;
    int baseLine = 0;
    cv::Size textSize = cv::getTextSize(welcomeText, fontFace, fontScale, thickness, &baseLine);

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);

        cv::putText(frame, welcomeText, cv::Point(width / 2 - (textSize.width / 2) + 5, textSize.height + 15), cv::FONT_HERSHEY_TRIPLEX, fontScale, cv::Scalar(0,0,0), thickness);
        cv::putText(frame, welcomeText, cv::Point(width / 2 - (textSize.width / 2), textSize.height + 10), cv::FONT_HERSHEY_TRIPLEX, fontScale, cv::Scalar(255,255,255), thickness);

        cv::Point point1 = coord(frame, player1);
        cv::Point point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
        cv::imshow("Cinekt", frame);

        if (point1.x < width * 0.25 && point1.y < height * 0.25) {
			PongGame *game = new PongGame(cap);
            game->pongGame();
        }

        if (point1.x > width * 0.75 && point1.y < height * 0.25) {
        	guessGame(cap);
        }

        int input = cv::waitKey(16);
        if (input == 27) {
            std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
            break;
        }
    }
}