#include "wallBreakerGame.h"
#include "objectTracking.h"


WallBreakerGame::WallBreakerGame(cv::VideoCapture webcam)
{
    this->webcam = webcam;
}

void WallBreakerGame::wallBreakerGame()
{
    srand(time(0));
    cv::Mat frame;
    width = webcam.get(cv::CAP_PROP_FRAME_WIDTH);
    height = webcam.get(cv::CAP_PROP_FRAME_HEIGHT);
    paddleLenght = height / 5;
    rectWidth = width / 10;

    paddle = { width / 2, height - 20 };
    ball = resetBall();


    while (ballCount > 0 && !checkEnd()) {
        webcam >> frame;

        // Mirroring webcam image horizontally
        cv::flip(frame, frame, +1);

        // Handling paddle movement
        cv::Point point1 = coord(frame, player1);
        paddle.xPos = point1.x;


        // Draw objects
        drawPaddle(frame, paddle);
        drawBricks(frame);
        moveBall(frame);
        cv::circle(frame, cv::Point(ball.xPos, ball.yPos), ballSize, cv::Scalar(255, 255, 255), -1);
        drawBallCount(frame);

        cv::imshow("Cinekt", frame);

        int input = cv::waitKey(5);
        if (input == 27) {
            std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
            break;
        }
    }
}

void WallBreakerGame::moveBall(cv::Mat screen)
{
    ball.xPos += ball.xSpeed;
    ball.yPos += ball.ySpeed;
    collision(screen);
}

void WallBreakerGame::collision(cv::Mat screen)
{
    if (ball.yPos - ballSize <= 0)
        ball.ySpeed *= -1;

    cv::Rect rect;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (bricks[i][j]) {
                if (ball.ySpeed < 0 && ball.yPos - ballSize <= (i + 1) * rectHeight)
                    if (ball.xPos >= j * rectWidth && ball.xPos <= (j + 1) * rectWidth) {
                        bricks[i][j] = 0;
                        ball.ySpeed *= -1;
                    }
            }
        }
    }

    if (ball.yPos + ballSize >= paddle.yPos - paddleWidth / 2) {
        if (ball.xPos + ballSize * 0.5 >= paddle.xPos - paddleLenght / 2 && ball.xPos - ballSize * 0.5 <= paddle.xPos + paddleLenght / 2) {
            ball.ySpeed *= -1.25;
        } else {
            ball = resetBall();
            ballCount--;
        }
    }
    if (ball.xPos - ballSize <= 0 || ball.xPos + ballSize >= width)
        ball.xSpeed *= -1;
}

void WallBreakerGame::drawPaddle(cv::Mat screen, WBPaddle paddle)
{
    cv::Rect rect(paddle.xPos - paddleLenght / 2, paddle.yPos - paddleWidth / 2, paddleLenght, paddleWidth);
    cv::rectangle(screen, rect, cv::Scalar(255, 255, 255), -1);
}

WBBall WallBreakerGame::resetBall()
{
    int ySpeed = 8 + rand() % 8;
    int xSpeed = 8 + rand() % 8;
    WBBall ball = {paddle.xPos, height - 40, xSpeed ,-ySpeed };
    return ball;
}

void WallBreakerGame::drawBallCount(cv::Mat screen)
{
    cv::putText(screen, std::to_string(ballCount), cv::Point(20, height - 20), cv::FONT_HERSHEY_SIMPLEX, 4, CV_RGB(255, 0, 0), 5);
}

void WallBreakerGame::drawBricks(cv::Mat screen)
{
    cv::Rect rect;
    cv::rectangle(screen, rect, cv::Scalar(255, 255, 255), -1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (bricks[i][j]) {
                rect = {j * rectWidth,i * rectHeight, rectWidth, rectHeight };
                switch (i) {
                    case 0:
                        cv::rectangle(screen, rect, cv::Scalar(255, 0, 0), 3);
                        break;
                    case 1:
                        cv::rectangle(screen, rect, cv::Scalar(0, 255, 0), 3);
                        break;
                    case 2:
                        cv::rectangle(screen, rect, cv::Scalar(0, 0, 255), 3);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

bool WallBreakerGame::checkEnd()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (bricks[i][j])
                return false;
        }
    }
    return true;
}