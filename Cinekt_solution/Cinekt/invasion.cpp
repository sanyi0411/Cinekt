#include "invasion.h"



Invasion::Invasion(cv::VideoCapture cap) : _cap(cap)
{
    int _width = _cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int _height = _cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}


Invasion::~Invasion()
{
}

std::vector<std::vector<boxTypes>> Invasion::createStartTable()
{
    std::vector<std::vector<boxTypes>> startTable;

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0) {
                startTable[i].push_back(GREEN);
            } else if (i > 19 || i == 19 && j >= 9 && j <= 11) {
                startTable[i].push_back(PLAYER);
            }
        }
    }

    return startTable;
}

cv::Mat Invasion::creatGameTable(std::vector<std::vector<boxTypes>> &gameTable)
{
    cv::Mat gameTableMat(cv::Size(400, 400), CV_8UC3, cv::Scalar::all(0));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (gameTable[i][j] == GREEN) {
                int posX = i * 20;
                int posY = j * 20;
                int rectWidth = 20;
                cv::Rect rect (posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTable, rect, cv::Scalar(0, 255, 0), -1);
            }
            else if (gameTable[i][j] == PLAYER) {
                int posX = i * 20;
                int posY = j * 20;
                int rectWidth = 20;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTable, rect, cv::Scalar(255, 255, 255), -1);
            }
        }
    }

}

void Invasion::creatBoxes(cv::Point point, int boxType)
{

}
