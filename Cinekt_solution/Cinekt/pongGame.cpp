#include "pongGame.h"
#include "objectTracking.h"

void pongGame(cv::VideoCapture webcam)
{
    cv::Mat frame;

    while (true) {
        webcam >> frame;
        cv::flip(frame, frame, +1);
        cv::Point point1 = coord(frame, palyer1);
        cv::Point point2 = coord(frame, palyer2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);
        cv::imshow("R", frame);


        cv::waitKey(16);
    }
}