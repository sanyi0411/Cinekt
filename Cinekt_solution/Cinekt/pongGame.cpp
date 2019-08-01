#include "pongGame.h"
#include "objectTracking.h"
#include "windows.h"


struct Ball {
    int xPos;
    int yPos;
    double xSpeed;
    double ySpeed;
};

struct Paddle {
    int xPos;
    int yPos;
    int ySpeed;
};

static int paddleLenght;
static int paddleWidth = 10;
static int ballSize = 20;
Ball ball;
Paddle paddle1;
Paddle paddle2;
int width;
int height;
int player1Score = 0;
int player2Score = 0;
std::vector<cv::Mat> screenshots;

void moveBall(cv::Mat screen);
void collision(cv::Mat screen);
Ball resetBall();
void drawScore(cv::Mat screen);
void drawPaddle(cv::Mat screen, Paddle paddle);
void slideShow();

void pongGame(cv::VideoCapture webcam)
{
    srand(time(0));
    cv::Mat frame;
    width = webcam.get(cv::CAP_PROP_FRAME_WIDTH);
    height = webcam.get(cv::CAP_PROP_FRAME_HEIGHT);
    paddleLenght = height / 5;

    ball = resetBall();
    paddle1 = { 25, height / 2, 0 };
    paddle2 = { width - 25, height / 2, 0 };

    while (player1Score < 5 && player2Score < 5) {
        webcam >> frame;

        // Mirroring webcam image horizontally
        cv::flip(frame, frame, +1);

        // Handling paddle movement
        cv::Point point1 = coord(frame, player1);
        paddle1.ySpeed = abs(paddle1.yPos - point1.y) / 50;
        paddle1.yPos = point1.y;
        cv::Point point2 = coord(frame, player2);
        paddle2.ySpeed = abs(paddle2.yPos - point2.y) / 50;
        paddle2.yPos = point2.y;

        // Draw objects
        cv::line(frame, cv::Point(width / 2, 0), cv::Point(width / 2, height), cv::Scalar(255, 255, 255), 5);
        drawPaddle(frame, paddle1);
        drawPaddle(frame, paddle2);
        moveBall(frame);
        cv::circle(frame, cv::Point(ball.xPos, ball.yPos), ballSize, cv::Scalar(255, 255, 255), -1);
        drawScore(frame);

        cv::imshow("Cinekt", frame);

        cv::waitKey(5);
    }
    slideShow();
}

void moveBall(cv::Mat screen)
{
    ball.xPos += ball.xSpeed;
    ball.yPos += ball.ySpeed;
    collision(screen);
}

void collision(cv::Mat screen)
{
    if (ball.xPos - ballSize <= paddle1.xPos + paddleWidth / 2) {
        if (ball.yPos >= paddle1.yPos - paddleLenght / 2 && ball.yPos <= paddle1.yPos + paddleLenght / 2) {
            ball.xSpeed *= -1.2;
        } else {
            ball = resetBall();
            player2Score++;
            screenshots.push_back(screen);
        }
    }
    if (ball.xPos + ballSize >= paddle2.xPos - paddleWidth / 2) {
        if (ball.yPos >= paddle2.yPos - paddleLenght / 2 && ball.yPos <= paddle2.yPos + paddleLenght / 2) {
            ball.xSpeed *= -1.2;
        } else {
            ball = resetBall();
            player1Score++;
            screenshots.push_back(screen);
        }
    }
    if (ball.yPos - ballSize <= 0 || ball.yPos + ballSize >= height)
        ball.ySpeed *= -1;
    //std::cout << ball.xSpeed << " " << ball.ySpeed << std::endl;
}

void drawPaddle(cv::Mat screen, Paddle paddle)
{
    cv::Rect rect(paddle.xPos - paddleWidth / 2, paddle.yPos - paddleLenght / 2, paddleWidth, paddleLenght);
    cv::rectangle(screen, rect, cv::Scalar(255, 255, 255), -1);
}

Ball resetBall()
{
    int xSpeed = 5 + rand() % 10;
    int ySpeed = 5 + rand() % 10;
    int direction = rand() % 2;
    Ball ball = { width / 2, height / 2, direction ? (xSpeed) : (-xSpeed),ySpeed };
    return ball;
}

void drawScore(cv::Mat screen)
{
    cv::putText(screen, std::to_string(player1Score),cv::Point(20, height - 20), cv::FONT_HERSHEY_SIMPLEX, 3, CV_RGB(255, 255, 255), 2);
    cv::putText(screen, std::to_string(player2Score),cv::Point(width - 20, height - 20), cv::FONT_HERSHEY_SIMPLEX, 3, CV_RGB(255, 255, 255), 2);
}

void slideShow()
{
    for (int i = 0; i < screenshots.size(); i++) {
        cv::imshow("ScreenShots", screenshots[i]);
        Sleep(1000);
    }
    cv::destroyWindow("ScreenShots");
}