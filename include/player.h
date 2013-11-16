#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string.h>
#define SQUARE 0
#define TANK   1
#ifndef PLAYER_H
#define PLAYER_H


/*
    OK what do I need from this Abstract Data Type?

    Variables:
    * Current position
    * Current rotation
    * Shape (Represented by some matrix)
    * Hitbox (Other objects not allowed inside this hit box)

    Member functions:
    Move(DIRECTION) could be public
    different move fucntions for each direction - private

    Also, this is a state machine. (Mealy or Moore?)



*/

class player
{
    public:
        player(int size=3, int SHAPE = 0, std::string player_name = "Player1"); ///Default object

        ///Self explanatory functions
        int turnLeft();
        int turnRight();
        int moveForward();
        int moveBack();
        int moveRight();
        int moveLeft();
        int strafeUp();
        int strafeDown();
        int strafeRight();
        int strafeLeft();
        int getSize();
        void setPosition(cv:: Point pos);
        std::string getPlayerName();
        cv::Point getCurrentPosition();
        ///Assigns a shape according to shape flags defined at the top of this file.
        ///Somethign wrong with this. Debug later.
        void assignShape(int SHAPE);


        ///For the drawing the object. Point starts at (1,1)
        int pointIsAlive(cv::Point point);

        virtual ~player();
    protected:
    private:
        int sizeOfObject;    ///Dimensions of object
        int **shape;        ///Holds the shape of the object
        int **state;        ///Holds current state of the object
        int **hitbox;
        std::string playerName;
        cv::Point position; ///Holds current position

};

#endif // PLAYER_H
