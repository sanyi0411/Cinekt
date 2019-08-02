#include "invasion.h"



Invasion::Invasion(cv::VideoCapture cap) : _cap(cap)
{
    _width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    _height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
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

void Invasion::createStartTable()
{
    std::vector<std::vector<boxTypes>> startTable(TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE - 1; j++) {
            if (i > TABLE_SIZE - 2 || i == TABLE_SIZE - 2 && j >= TABLE_SIZE / 2 - 1 && j <= TABLE_SIZE / 2 + 1) {
                startTable[i].push_back(PLAYER);
            } else {
                startTable[i].push_back(BLANK);
            }
        }
    }
    setGameTable(startTable);
}

void Invasion::runGame()
{
    createStartTable();

    cv::Mat frame;
    cv::Mat game;

    clock_t projectileBegin = clock();
    clock_t boxBegin = clock();
    clock_t fireBegin = clock();

    creatBoxes();
    int amountOfLine = 0;

    while (_run) {
        
        _cap >> frame;
        srand(time(NULL));
        // Mirroring webcam image horizontally
        cv::flip(frame, frame, +1);

        // Handling paddle movement
        cv::Point point1 = coord(frame, player1);
        int point1X = point1.x;
        movedPlayer(point1X);
        cv::Point point2 = coord(frame, player2);
        int fireY = point2.y;

        
        
        clock_t projectileClock = (clock() - projectileBegin) / CLOCKS_PER_SEC;
        clock_t boxClock = (clock() - boxBegin) / CLOCKS_PER_SEC;
        clock_t fireClock = (clock() - fireBegin) / CLOCKS_PER_SEC;
        if (projectileClock >= 0.2) {
            movedProjectile();
            projectileBegin = clock();
        }
        if (boxClock >= 2.0) {
            movedBoxes();
            if (amountOfLine != AMOUNT_OF_LINE) {
                creatBoxes();
                amountOfLine++;
            }
            boxBegin = clock();
        }
        saveFirePoints(fireY);
        if (fireClock >= 0.2) {
            if (fire()) {
                creatProjectile();
            }
        }
        game = creatGameTable();
        cv::imshow("Cinekt", frame);
        cv::imshow("Invasion", game);
        cv::waitKey(16);
    }
    _cap.release();
    cv::destroyAllWindows();
}

cv::Mat Invasion::creatGameTable()
{
    cv::Mat gameTableMat(cv::Size(WINDOW_PARAMETER, WINDOW_PARAMETER), CV_8UC3, cv::Scalar::all(0));

    for (int i = 0; i < TABLE_SIZE - 1; i++) {
        for (int j = 0; j < TABLE_SIZE - 1; j++) {
            if (_gameTable[i][j] == GREEN) {
                int posX = j * RECTANGLE_PARAMETER;
                int posY = i * RECTANGLE_PARAMETER;
                int rectWidth = RECTANGLE_PARAMETER;
                cv::Rect rect (posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(0, 255, 0), -1);
            } else if (_gameTable[i][j] == PLAYER) {
                int posX = j * RECTANGLE_PARAMETER;
                int posY = i * RECTANGLE_PARAMETER;
                int rectWidth = RECTANGLE_PARAMETER;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(255, 255, 255), -1);
            } else if (_gameTable[i][j] == PROJECTILE) {
                int posX = j * RECTANGLE_PARAMETER;
                int posY = i * RECTANGLE_PARAMETER;
                int rectWidth = RECTANGLE_PARAMETER;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(255, 0, 0), -1);
            } else if (_gameTable[i][j] == RED) {
                int posX = j * RECTANGLE_PARAMETER;
                int posY = i * RECTANGLE_PARAMETER;
                int rectWidth = RECTANGLE_PARAMETER;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(0, 0, 255), -1);
            } else if (_gameTable[i][j] == YELLOW) {
                int posX = j * RECTANGLE_PARAMETER;
                int posY = i * RECTANGLE_PARAMETER;
                int rectWidth = RECTANGLE_PARAMETER;
                cv::Rect rect(posX, posY, rectWidth, rectWidth);
                cv::rectangle(gameTableMat, rect, cv::Scalar(0, 255, 255), -1);
            }
        }
    }
    return gameTableMat;
}

void Invasion::creatBoxes()
{
    for (int i = 0; i < TABLE_SIZE - 1; i++) {
        int randNumber = rand() % 10;
        if(randNumber == 0) {
            _gameTable[0][i] = BLANK;
        } else if (randNumber < 5) {
            _gameTable[0][i] = GREEN;
        } else if (randNumber < 8) {
            _gameTable[0][i] = YELLOW;
        } else if (randNumber < 10) {
            _gameTable[0][i] = RED;
        }
    }
}

void Invasion::movedPlayer(int x)
{
    int recalculated = (x - _width * 0.25) * WINDOW_PARAMETER / (_width * 0.25);
    _gameTable[TABLE_SIZE - 2][_playerX - 1] = BLANK;
    _gameTable[TABLE_SIZE - 2][_playerX] = BLANK;
    _gameTable[TABLE_SIZE - 2][_playerX + 1] = BLANK;
    int newPosition = recalculated / (TABLE_SIZE - 1);
    
    if(newPosition < 0) {
        newPosition = 0;
    }
    if (newPosition > TABLE_SIZE - 2) {
        newPosition = TABLE_SIZE - 2;
    }

    setPlayerX(newPosition);
    _gameTable[TABLE_SIZE - 2][newPosition - 1] = PLAYER;
    _gameTable[TABLE_SIZE - 2][newPosition] = PLAYER;
    _gameTable[TABLE_SIZE - 2][newPosition + 1] = PLAYER;
}

void Invasion::movedProjectile()
{
    for (int i = 0; i < _projectilePoint.size(); i ++) {
        _gameTable[_projectilePoint[i][0]][_projectilePoint[i][1]] = BLANK;

        if (_projectilePoint[i][0] != 0) {
            if(_gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] != BLANK) {
                if (_gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] == RED) {
                    _gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] = YELLOW;
                    destroyProjectile();
                } else if (_gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] == YELLOW) {
                    _gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] = GREEN;
                    destroyProjectile();
                } else if(_gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] == GREEN) {
                    _gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] = BLANK;
                    destroyProjectile();
                }
            } else {
                _gameTable[_projectilePoint[i][0] - 1][_projectilePoint[i][1]] = PROJECTILE;
                _projectilePoint[i][0]--;
            }
        }
        else {
            destroyProjectile();
        }
    }
}

void Invasion::movedBoxes()
{
    std::vector<std::vector<boxTypes>> newGameTable = _gameTable;
    //Fill up first row
    for (int i = 0; i < TABLE_SIZE - 1; i ++) {
        newGameTable[0][i] = BLANK;
    }

    //Move boxes one unit down
    for (int i = 0; i < TABLE_SIZE - 1; i++) {
        for (int j = 0; j < TABLE_SIZE - 1; j++) {
            if (_gameTable[i][j] == PROJECTILE) {
                continue;
            }else if (_gameTable[i][j] == PLAYER) {
                continue;
            }else if (_gameTable[i][j] == BLANK) {
                if (_gameTable[i + 1][j] != PROJECTILE && _gameTable[i + 1][j] != PLAYER) {
                    newGameTable[i + 1][j] = BLANK;
                    continue;
                } else {
                    continue;
                }
            }else {
                if (_gameTable[i + 1][j] == PROJECTILE) {
                    if (_gameTable[i][j] == RED) {
                        newGameTable[i + 1][j] == YELLOW;
                        destroyProjectileWithCollision(i + 1);
                        continue;
                    } else if (_gameTable[i][j] == YELLOW) {
                        newGameTable[i + 1][j] == GREEN;
                        destroyProjectileWithCollision(i + 1);
                        continue;
                    } else if (_gameTable[i][j] == GREEN) {
                        newGameTable[i + 1][j] == BLANK;
                        destroyProjectileWithCollision(i + 1);
                        continue;
                    }
                } else if (_gameTable[i + 1][j] == PLAYER) {
                    if (_gameTable[i][j] == RED || _gameTable[i][j] == YELLOW || _gameTable[i][j] == GREEN) {
                        gameOver();
                    }
                } else {
                    newGameTable[i + 1][j] = _gameTable[i][j];
                }
            }
        }
    }
    setGameTable(newGameTable);
}

void Invasion::destroyProjectile()
{
    std::vector<std::vector<int>>::iterator it = _projectilePoint.begin();
    _projectilePoint.erase(it);
}

void Invasion::destroyProjectileWithCollision(int position)
{
    std::vector<std::vector<int>>::iterator it = _projectilePoint.begin();
    for (it ; it != _projectilePoint.end(); it++) {
        if (it->at(0) == position) {
            _projectilePoint.erase(it);
            break;
        }
    }
}

void Invasion::gameOver()
{
    _run = false;
}

void Invasion::creatProjectile()
{
    _gameTable[TABLE_SIZE - 3][_playerX] = PROJECTILE;
    std::vector<int> point = { TABLE_SIZE - 3, _playerX };
    _projectilePoint.push_back(point);
}

void Invasion::saveFirePoints(int y)
{
    _fire.push_back(y);
    if (_fire.size() > 2) {
        auto it = _fire.begin();
        _fire.erase(it);
    }
}

bool Invasion::fire()
{
    if (_fire[0] - _fire[1] > _height * 0.01) {
        return true;
    }
    return false;
}
