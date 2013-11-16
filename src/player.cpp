#include "player.h"
#define SQUARE 0
#define TANK   1

int tank[][3] = {{0,1,0},{1,1,1},{1,0,1}};

using namespace cv;

player::player(int size, int SHAPE, string player_name)
{
    //ctor
    int i,j;

    ///Making a new array of size given
    shape = new int*[size];
    for(i=0;i<size;i++) shape[i] = new int[size];
    ///Fill with zeros
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            shape[i][j] = 1;
        }
    }

    ///filling array with default shape(square)
    ///Something wrong with this debug later.
    //assignShape(SHAPE);
    if(SHAPE == SQUARE)
    {
        for(i=0;i<size;i++)
        {
            for(j=0;j<size;j++)
            {
                shape[i][j] = 1;
            }
        }
    }

    if(SHAPE == TANK)
    {
        for(i=0;i<size;i++)
        {
            for(j=0;j<size;j++)
            {
                shape[i][j] = tank[i][j];
            }
        }
    }



    ///Default location (10,10)
    position = Point(10, 10);
    sizeOfObject = size;
    playerName = player_name;

}

int player::pointIsAlive(Point point)
{
    return shape[point.x - 1][sizeOfObject - point.y];
}

std::string player::getPlayerName()
{
    return playerName;
}

void player::setPosition(Point point)
{
    position = point;
}

Point player::getCurrentPosition()
{
    return position;
}

int player::getSize()
{
    return sizeOfObject;
}

int player::strafeUp()
{
    position.y +=1;
    return 1;
}

int player::strafeDown()
{
    position.y -= 1;
    return 1;
}

int player::strafeLeft()
{
    position.x -= 1;
    return 1;
}

int player::strafeRight()
{
    position.x += 1;
    return 1;
}

///Something wrong with this. Come back later.
void player::assignShape(int SHAPE)
{
    int i,j;
    if(SHAPE == SQUARE)
    {
        for(i=0;i<sizeOfObject;i++)
        {
            for(j=0;j<sizeOfObject;j++)
            {
                shape[i][j] = tank[i][j];
            }
        }
    }
}

player::~player()
{
    //dtor
}
