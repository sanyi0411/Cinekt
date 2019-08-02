#include <iostream>
#include <time.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Windows.h>
#include <mmsystem.h>
#include <WinUser.h>
#pragma comment(lib, "WinMM.Lib")
#include "objectTracking.h"
#include "invasion.h"
#include "pongGame.h"
#include "guessGame.h"
<<<<<<< HEAD
#include "dinoGame.h"
=======
#include "wallBreakerGame.h"
>>>>>>> 930ff6f88540dd3a99c8d5c2df939ce16fc0e59a

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

    cv::Size welcomeSize = cv::getTextSize("Welcome to Cinekt!", cv::FONT_HERSHEY_TRIPLEX, 3, 5, 0);

    cv::Size pongSize = cv::getTextSize("Pong", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
    cv::Size dinoSize = cv::getTextSize("Dino", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
    cv::Size invadersSize = cv::getTextSize("Invaders", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
    cv::Size guessSize = cv::getTextSize("Guess", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);
    cv::Size wallBreakerSize = cv::getTextSize("Wall Breaker", cv::FONT_HERSHEY_TRIPLEX, 2, 2, 0);

    while (true) {
        cap >> frame;
        cv::flip(frame, frame, +1);

        /*Main menu titles*/
        cv::putText(frame, "Welcome to Cinekt!", cv::Point(width / 2 - (welcomeSize.width / 2) + 5, welcomeSize.height + 25), cv::FONT_HERSHEY_TRIPLEX, 3, cv::Scalar(0, 0, 0), 5);
        cv::putText(frame, "Welcome to Cinekt!", cv::Point(width / 2 - (welcomeSize.width / 2), welcomeSize.height + 20), cv::FONT_HERSHEY_TRIPLEX, 3, cv::Scalar(255, 255, 255), 5);

        cv::putText(frame, "Pong", cv::Point(width / 8 - (pongSize.width / 2) + 3, welcomeSize.height + 18 + 4 * pongSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, "Pong", cv::Point(width / 8 - (pongSize.width / 2), welcomeSize.height + 15 + 4 * pongSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2);
        cv::rectangle(frame, cv::Point(width / 8 - (pongSize.width / 2) - 7, welcomeSize.height + 28 + 4 * pongSize.height), cv::Point(width / 8 + (pongSize.width / 2) + 13, welcomeSize.height + 8 + 3 * pongSize.height), cv::Scalar(0, 0, 0), 2);
        cv::rectangle(frame, cv::Point(width / 8 - (pongSize.width / 2) - 10, welcomeSize.height + 25 + 4 * pongSize.height), cv::Point(width / 8 + (pongSize.width / 2) + 10, welcomeSize.height + 5 + 3 * pongSize.height), cv::Scalar(255, 255, 255), 2);

        cv::putText(frame, "Dino", cv::Point(3 * (width / 8) - (dinoSize.width / 2) + 3, welcomeSize.height + 18 + 4 * dinoSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, "Dino", cv::Point(3 * (width / 8) - (dinoSize.width / 2), welcomeSize.height + 15 + 4 * dinoSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2);
        cv::rectangle(frame, cv::Point(3 * (width / 8) - (dinoSize.width / 2) - 7, welcomeSize.height + 28 + 4 * dinoSize.height), cv::Point(3 * (width / 8) + (dinoSize.width / 2) + 13, welcomeSize.height + 8 + 3 * dinoSize.height), cv::Scalar(0, 0, 0), 2);
        cv::rectangle(frame, cv::Point(3 * (width / 8) - (dinoSize.width / 2) - 10, welcomeSize.height + 25 + 4 * dinoSize.height), cv::Point(3 * (width / 8) + (dinoSize.width / 2) + 10, welcomeSize.height + 5 + 3 * dinoSize.height), cv::Scalar(255, 255, 255), 2);

        cv::putText(frame, "Invaders", cv::Point(5 * (width / 8) - (invadersSize.width / 2) + 3, welcomeSize.height + 18 + 4 * invadersSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, "Invaders", cv::Point(5 * (width / 8) - (invadersSize.width / 2), welcomeSize.height + 15 + 4 * invadersSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2);
        cv::rectangle(frame, cv::Point(5 * (width / 8) - (invadersSize.width / 2) - 7, welcomeSize.height + 28 + 4 * invadersSize.height), cv::Point(5 * (width / 8) + (invadersSize.width / 2) + 13, welcomeSize.height + 8 + 3 * invadersSize.height), cv::Scalar(0, 0, 0), 2);
        cv::rectangle(frame, cv::Point(5 * (width / 8) - (invadersSize.width / 2) - 10, welcomeSize.height + 25 + 4 * invadersSize.height), cv::Point(5 * (width / 8) + (invadersSize.width / 2) + 10, welcomeSize.height + 5 + 3 * invadersSize.height), cv::Scalar(255, 255, 255), 2);

        cv::putText(frame, "Guess", cv::Point(7 * (width / 8) - (guessSize.width / 2) + 3, welcomeSize.height + 18 + 4 * guessSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, "Guess", cv::Point(7 * (width / 8) - (guessSize.width / 2), welcomeSize.height + 15 + 4 * guessSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2);
        cv::rectangle(frame, cv::Point(7 * (width / 8) - (guessSize.width / 2) - 7, welcomeSize.height + 28 + 4 * guessSize.height), cv::Point(7 * (width / 8) + (guessSize.width / 2) + 13, welcomeSize.height + 8 + 3 * guessSize.height), cv::Scalar(0, 0, 0), 2);
        cv::rectangle(frame, cv::Point(7 * (width / 8) - (guessSize.width / 2) - 10, welcomeSize.height + 25 + 4 * guessSize.height), cv::Point(7 * (width / 8) + (guessSize.width / 2) + 10, welcomeSize.height + 5 + 3 * guessSize.height), cv::Scalar(255, 255, 255), 2);

        cv::putText(frame, "Wall Breaker", cv::Point(width / 2 - (wallBreakerSize.width / 2) + 3, height - 2 * wallBreakerSize.height + 3), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(0, 0, 0), 2);
        cv::putText(frame, "Wall Breaker", cv::Point(width / 2 - (wallBreakerSize.width / 2), height - 2 * wallBreakerSize.height), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(255, 255, 255), 2);
        cv::rectangle(frame, cv::Point(width / 2 - (wallBreakerSize.width / 2) - 7, height - 2 * wallBreakerSize.height + 13), cv::Point(width / 2 + (wallBreakerSize.width / 2) + 13, height - 3 * wallBreakerSize.height - 7), cv::Scalar(0, 0, 0), 2);
        cv::rectangle(frame, cv::Point(width / 2 - (wallBreakerSize.width / 2) - 10, height - 2 * wallBreakerSize.height + 10), cv::Point(width / 2 + (wallBreakerSize.width / 2) + 10, height - 3 * wallBreakerSize.height - 10), cv::Scalar(255, 255, 255), 2);

        /*Player coordinates*/
        cv::Point point1 = coord(frame, player1);
        cv::Point point2 = coord(frame, player2);
        cv::circle(frame, point1, 20, cv::Scalar(0, 0, 255), -1);
        cv::circle(frame, point2, 20, cv::Scalar(255, 0, 0), -1);

        cv::imshow("Cinekt", frame);

        /*Choosing a game*/
        if (point1.x >= (width / 8) - (pongSize.width / 2) - 10 && point1.x <= (width / 8) + (pongSize.width / 2) + 10 &&
            point1.y >= welcomeSize.height + 5 + 3 * pongSize.height && point1.y <= welcomeSize.height + 25 + 4 * pongSize.height) {
            PongGame *game = new PongGame(cap);
            game->pongGame();
        }

        if (point1.x >= 3 * (width / 8) - (dinoSize.width / 2) - 10 && point1.x <= 3 * (width / 8) + (dinoSize.width / 2) + 13 &&
            point1.y >= welcomeSize.height + 5 + 3 * dinoSize.height && point1.y <= welcomeSize.height + 25 + 4 * dinoSize.height) {
            std::cout << "Dino game" << std::endl;
            DinoGame *game = new DinoGame(cap);
            game->dinoGame();
        }

        if (point1.x >= 5 * width / 8 - (invadersSize.width / 2) - 7 && point1.x <= 5 * (width / 8) + (invadersSize.width / 2) + 13 &&
            point1.y >= welcomeSize.height + 5 + 3 * invadersSize.height && point1.y <= welcomeSize.height + 25 + 4 * invadersSize.height) {
            Invasion game(cap);
            game.runGame();
        }

        if (point1.x >= 7 * (width / 8) - (guessSize.width / 2) - 7 && point1.x <= 7 * (width / 8) + (guessSize.width / 2) + 10 &&
            point1.y >= welcomeSize.height + 5 + 3 * guessSize.height && point1.y <= welcomeSize.height + 25 + 4 * guessSize.height) {
            guessGame(cap);
        }

        if (point1.x >= width / 2 - (wallBreakerSize.width / 2) - 10 && point1.x <= width / 2 + (wallBreakerSize.width / 2) + 13 &&
            point1.y >= height - 3 * wallBreakerSize.height - 10 && point1.y <= height - 2 * wallBreakerSize.height + 10) {
            WallBreakerGame *game = new WallBreakerGame(cap);
            game->wallBreakerGame();
        }

        if (point1.x >= 5 * width / 8 - (invadersSize.width / 2) - 7 && point1.x <= 5 * (width / 8) + (invadersSize.width / 2) + 13 &&
            point1.y >= welcomeSize.height + 5 + 3 * invadersSize.height && point1.y <= welcomeSize.height + 25 + 4 * invadersSize.height) {
            Invasion invasion(cap);
            invasion.runGame();
        }

        int input = cv::waitKey(16);
        if (input == 27) {
            std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
            break;
        }
    }
}