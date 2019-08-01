#include "invasion.h"



Invasion::Invasion(cv::VideoCapture cap) : _cap(cap)
{
    int _width = _cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int _height = _cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}


Invasion::~Invasion()
{
}

void Invasion::setGameTable(std::vector<std::vector<boxTypes>> &gameTable)
{
    _gameTable = gameTable;
}

std::vector<std::vector<boxTypes>> Invasion::getGameTable()
{
    return _gameTable;
}

void Invasion::setPlayerX(int playerX)
{
    _playerX = playerX;
}

std::vector<std::vector<boxTypes>> Invasion::createStartTable()
{
    std::vector<std::vector<boxTypes>> startTable(21);

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0) {
                startTable[i].push_back(GREEN);
            } else if (i > 19 || i == 19 && j >= 9 && j <= 11) {
                startTable[i].push_back(PLAYER);
            } else {
                startTable[i].push_back(BLANK);
            }
        }
    }

    return startTable;
}

cv::Mat Invasion::creatGameTable()
{
    cv::Mat gameTableMat(cv::Size(400, 400), CV_8UC3, cv::Scalar::all(0));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (_gameTable[i][j] == GREEN) {
                int posX = j * 20;
                int posY = i * 20;
                int rectWidth = 20;
                cv::Rect rect (posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(0, 255, 0), -1);
            } else if (_gameTable[i][j] == PLAYER) {
                int posX = j * 20;
                int posY = i * 20;
                int rectWidth = 20;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(255, 255, 255), -1);
            } else if (_gameTable[i][j] == PROJECTILE) {
                int posX = j * 20;
                int posY = i * 20;
                int rectWidth = 20;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(255, 0, 0), -1);
            }
        }
    }
    return gameTableMat;
}

void Invasion::creatBoxes(cv::Point point, int boxType)
{

}

void Invasion::creatMovedPlayer(int &x)
{
    _gameTable[19][_playerX - 1] = BLANK;
    _gameTable[19][_playerX] = BLANK;
    _gameTable[19][_playerX + 1] = BLANK;
    int newPosition = x / 20;
    
    if(newPosition < 0) {
        newPosition = 0;
    }
    if (newPosition > 19) {
        newPosition = 19;
    }

    setPlayerX(newPosition);
    _gameTable[19][newPosition - 1] = PLAYER;
    _gameTable[19][newPosition] = PLAYER;
    _gameTable[19][newPosition + 1] = PLAYER;
}