#include "pongGame.h"
#include "objectTracking.h"


PongGame::PongGame(cv::VideoCapture webcam)
{
    this->webcam = webcam;
}

void PongGame::pongGame()
{
    srand(time(0));
    cv::Mat frame;
    width = webcam.get(cv::CAP_PROP_FRAME_WIDTH);
    height = webcam.get(cv::CAP_PROP_FRAME_HEIGHT);
    paddleLenght = height / 5;
    player1Score = 0;
    player2Score = 0;
    screenshots.clear();

    ball = resetBall();
    paddle1 = { 25, height / 2};
    paddle2 = { width - 25, height / 2};

    while (player1Score < win_cond && player2Score < win_cond) {
        webcam >> frame;

        // Mirroring webcam image horizontally
        cv::flip(frame, frame, +1);

        // Handling paddle movement
        cv::Point point1 = coord(frame, player1);
        paddle1.yPos = point1.y;
        cv::Point point2 = coord(frame, player2);
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
    std::cout << "slideshow\n";
    slideShow();
}

void PongGame::moveBall(cv::Mat screen)
{
    ball.xPos += ball.xSpeed;
    ball.yPos += ball.ySpeed;
    collision(screen);
}

void PongGame::collision(cv::Mat screen)
{
    if (ball.xPos - ballSize <= paddle1.xPos + paddleWidth / 2) {
        if (ball.yPos >= paddle1.yPos - paddleLenght / 2 && ball.yPos <= paddle1.yPos + paddleLenght / 2) {
            ball.xSpeed *= -1.25;
        } else {
            screenshots.push_back(cv::Mat(screen.clone()));
            ball = resetBall();
            player2Score++;
        }
    }
    if (ball.xPos + ballSize >= paddle2.xPos - paddleWidth / 2) {
        if (ball.yPos >= paddle2.yPos - paddleLenght / 2 && ball.yPos <= paddle2.yPos + paddleLenght / 2) {
            ball.xSpeed *= -1.25;
        } else {
            screenshots.push_back(screen.clone());
            ball = resetBall();
            player1Score++;
        }
    }
    if (ball.yPos - ballSize <= 0 || ball.yPos + ballSize >= height)
        ball.ySpeed *= -1;
}

void PongGame::drawPaddle(cv::Mat screen, Paddle paddle)
{
    cv::Rect rect(paddle.xPos - paddleWidth / 2, paddle.yPos - paddleLenght / 2, paddleWidth, paddleLenght);
    cv::rectangle(screen, rect, cv::Scalar(255, 255, 255), -1);
}

Ball PongGame::resetBall()
{
    int xSpeed = 8 + rand() % 8;
    int ySpeed = 8 + rand() % 8;
    int direction = rand() % 2;
    Ball ball = { width / 2, height / 2, direction ? (xSpeed) : (-xSpeed),ySpeed };
    return ball;
}

void PongGame::drawScore(cv::Mat screen)
{
    cv::putText(screen, std::to_string(player1Score),cv::Point(20, height - 20), cv::FONT_HERSHEY_SIMPLEX, 4, CV_RGB(255, 0, 0), 5);
    cv::putText(screen, std::to_string(player2Score),cv::Point(width - 120, height - 20), cv::FONT_HERSHEY_SIMPLEX, 4, CV_RGB(255, 0, 0 ), 5);
}

void PongGame::slideShow()
{
    for (int i = 0; i < screenshots.size(); i++) {
        cv::imshow("Cinekt", screenshots[i]);
        cv::waitKey(1000);
    }
}