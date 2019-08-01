#include "invasion.h"



Invasion::Invasion(cv::VideoCapture cap) : _cap(cap)
{
    int _width = _cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int _height = _cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}


Invasion::~Invasion()
{
}

void Invasion::creatGameTable(std::vector<std::vector<int>>* gameTable)
{

}

void Invasion::creatBoxes(cv::Point point)
{

}
