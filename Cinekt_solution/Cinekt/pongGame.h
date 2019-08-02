#pragma once
#include "opencv2/highgui.hpp"

struct Ball {
    int xPos;
    int yPos;
    double xSpeed;
    double ySpeed;
};

struct Paddle {
    int xPos;
    int yPos;
};

class PongGame {
public:
    PongGame(cv::VideoCapture webcam);
    void pongGame();
private:
    void moveBall(cv::Mat screen);
    void collision(cv::Mat screen);
    Ball resetBall();
    void drawScore(cv::Mat screen);
    void drawPaddle(cv::Mat screen, Paddle paddle);
    void slideShow();

    cv::VideoCapture webcam;
    int paddleLenght;
    const int paddleWidth = 10;
    const int ballSize = 20;
    int win_cond = 3;
    Ball ball;
    Paddle paddle1;
    Paddle paddle2;
    int width;
    int height;
    int player1Score;
    int player2Score;
    std::vector<cv::Mat> screenshots;
};