#ifndef GAMEGRAPHICS_H
#define GAMEGRAPHICS_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define CELL_LENGTH 20
#include <gridGraphics.h>
#include "player.h"


class gameGraphics : public gridGraphics
{
    public:
        gameGraphics(cv::Mat &image): gridGraphics(image){};
        gameGraphics(cv::Mat &image, int cellLength):gridGraphics(image, cellLength){};

        ///Draw function in regular x-y coordinate system. The fillCell function uses
        ///Array indexing which is inconvenient. The cartesian system is easier to work with
        void drawPoint(int R, int G, int B, cv::Point point);
        cv::Point toDeCartes(cv::Point gridPoint);

        ///Draw an object in the game frame
        void drawObject(int **array);
        void drawObject(player &player_object, int R=0,int G=0,int B=0);

        ///Clears the frame of previous changes
        void clearFrame();

        virtual ~gameGraphics();
    protected:
    private:
    player player1;
};

#endif // GAMEGRAPHICS_H
