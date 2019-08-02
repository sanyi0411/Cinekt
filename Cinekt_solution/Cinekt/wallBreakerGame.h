#pragma once
#include "opencv2/highgui.hpp"

struct WBBall {
    int xPos;
    int yPos;
    double xSpeed;
    double ySpeed;
};

struct WBPaddle {
    int xPos;
    int yPos;
};

class WallBreakerGame
{
public:
    WallBreakerGame(cv::VideoCapture webcam);
    void wallBreakerGame();
private:
    void moveBall(cv::Mat screen);
    void collision(cv::Mat screen);
    WBBall resetBall();
    void drawPaddle(cv::Mat screen, WBPaddle paddle);
    void drawBallCount(cv::Mat screen);
    void drawBricks(cv::Mat screen);
    bool checkEnd();

    int bricks[3][10] = { {1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1}, };
    cv::VideoCapture webcam;
    int paddleLenght;
    const int paddleWidth = 10;
    const int ballSize = 20;
    int rectWidth;
    int yOffset = 30;
    int xOffset;
    const int rectHeight = 30;
    WBBall ball;
    WBPaddle paddle;
    int ballCount = 3;
    int width;
    int height;
};