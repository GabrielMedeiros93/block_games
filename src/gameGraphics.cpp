#include "gameGraphics.h"
using namespace cv;

//gameGraphics::gameGraphics(Mat &image)
//{
    //ctor
//}

Point gameGraphics::toDeCartes(Point gridPoint)
{
    gridPoint.y = getRows() - gridPoint.y + 1;
    return gridPoint;
}

void gameGraphics::drawPoint(int R, int G, int B, Point point)
{
    if((point.x>0) && (point.y>0)
        &&(point.y<=getRows())
        &&(point.x<=getCols()))
    {
        point.y = getRows() - point.y + 1;
        fillTargetCell(R, G, B, point);
    }

}

void gameGraphics::drawObject(player &player_object, int R,int G,int B)
{
    int u,v=1;
    Point i = player_object.getCurrentPosition();
    i = i + Point(-1*((int)(player_object.getSize()/2)),-1*((int)(player_object.getSize()/2)));
    for(v=1;v<=player_object.getSize();v++)
    {
        for(u=1;u<=player_object.getSize();u++)
        {
            if(player_object.pointIsAlive(Point(u,v)))drawPoint(R,G,B, i + Point(u-1, v-1));
        }

    }

}

void gameGraphics::clearFrame()
{
    fillAllCells(255,255,255);
}

gameGraphics::~gameGraphics()
{
    //dtor
}
