#include "dinoGame.h"

DinoGame::DinoGame(cv::VideoCapture cap)
{
    this->cap = cap;
}

void DinoGame::dinoGame()
{
    INPUT ip;

    cv::Mat frame;
    cv::Mat blur;
    cv::Mat hsv;
    cv::Mat mask;

    cv::Scalar scalarLower(20, 100, 100);
    cv::Scalar scalarUpper(30, 255, 255);

    //cap.set(cv::CAP_PROP_FRAME_WIDTH, 1000);
    //cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1000);

    _width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    _height = cap.get(cv::CAP_PROP_FRAME_WIDTH);

    while (cv::waitKey(30) != 'q') {
        cap >> frame;
        if (frame.empty()) {
            std::cout << "Video camera is disconnected" << std::endl;
            std::cin.get();
            break;
        }

        cv::flip(frame, frame, +1);

        // Handling dino movement
        cv::Point point = coord(frame, player1);

        /*
        cv::blur(frame, blur, cv::Size(3, 3));
        cvtColor(blur, hsv, cv::COLOR_BGR2HSV);
        // Thresholding
        cv::inRange(hsv, scalarLower, scalarUpper, mask);

        // Morphological transformations
        erode(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        dilate(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        dilate(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        erode(mask, mask, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        // Contours
        std::vector<std::vector<cv::Point>> vContours;
        cv::findContours(mask, vContours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        cv::drawContours(mask, vContours, -1, (122, 122, 0), 3);
        std::vector<std::vector<cv::Point>> vWContours;
        vWContours = vContours;

        // Calculate the moments of the thresholded image
        cv::Moments oMoments = cv::moments(mask, true);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        if (dArea > 25000) {
            //cx = dM10 / dArea;
            //cy = dM01 / dArea;
            cv::Point p(dM10 / dArea, dM01 / dArea);
            //std::cout << p << std::endl;
            cv::circle(mask, p, 5, cv::Scalar(128, 0, 0), -1);
        }
        _cy = dM01 / dArea;
        */
        cv::Mat grayScale;
        cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);
        mask = cv::Mat::zeros(frame.size(), CV_8UC1);
        mask += grayScale * 0.1;
        cv::circle(mask, point, 5, cv::Scalar(128, 0, 0), -1);

        _cy = point.y;
        int c;

        for (int k = 0; k < 2; k++) {
            _bkey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x25\x26"[k]))) != 0;
        }

        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        if (_cy < _height / 7 && _center == true) {
            _center = false;
            std::cout << "Jump" << std::endl;
            ip.ki.wVk = 0x26;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));
            _upKeyHold = true;
            _up = true;
        }
        else {
            _upKeyHold = false;
        }
        if (_cy > _height / 7 && _cy < _height / 2.5 && _up == true || _down == true) {
            _center = true;
            _up = false;
            std::cout << "Run" << std::endl;
        }
        if (_cy > _width / 2.5 && _center == true) {
            _center = false;
            _down = true;
            std::cout << "Duck" << std::endl;
            // This is for the newer version, you can duck in it as well 
            //ip.ki.wVk = 0x28;
            //ip.ki.dwFlags = 0;
            //SendInput(1, &ip, sizeof(INPUT));
            _downKeyHold = true;
        }
        else {
            _downKeyHold = false;
        }

        cv::line(mask, cv::Point(0, _width / 7.), cv::Point(_width, _width / 7.), cv::Scalar(255), 5);
        cv::line(mask, cv::Point(0, _width / 2.5), cv::Point(_width, _width / 2.5), cv::Scalar(255), 5);
        cv::imshow("Live camera feed", mask);
    }
}
