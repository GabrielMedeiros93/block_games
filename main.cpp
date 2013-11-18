#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "gameGraphics.h"
#include "player.h"

#define CELL_SIZE 20

using namespace std;

int sim_start=0;

void mouseEventInGame(int event, int x, int y, int flags, void *param);
player player1(3, 1,"Player");
//player friendlyBullet()

int main()
{
    using namespace cv;

    ///Variable declarations
    Mat frame(900, 1600, CV_8UC3, Scalar(0)); ///The current frame of the animation
    Mat controls(500,500,CV_8UC3, Scalar(0)); ///The controls
    namedWindow("GameWindow"); ///Window where the gaming action happens!!
    //player player1(3, 1,"Player");
    char keypress;

    gameGraphics gameFrame(frame, CELL_SIZE); ///Initialize grid graphics with the frame

    gameFrame.fillAllCells(255,255,255);

    //gameFrame.fillTargetCell(0,0,0, cv::Point(2 ,gameFrame.getRows() - 5 + 1));
    gameFrame.drawPoint(0,0,0, cv::Point(81,45));
    gameFrame.drawObject(player1);

    cv::Point k = cv::Point(1,2);
    cout<<"X:"<<k.x<<","<<"Y:"<<k.y<<endl;

    ///Set mouse callback for detecting clicks
    setMouseCallback("GameWindow", mouseEventInGame, &gameFrame);

    while(1)
    {
        imshow("GameWindow", frame);
        gameFrame.clearFrame();
        gameFrame.drawObject(player1, 0,255,0);

        keypress = waitKey(50);

        if(keypress==27){break; cout<<"Key pressed: "<<keypress<<endl;}
        //if(keypress=='s') {sim_start ^= 1; cout<<"Key pressed: "<<keypress<<endl;}
        if(keypress=='w') {player1.strafeUp(); }
        if(keypress=='a') {player1.strafeLeft(); }
        if(keypress=='s') {player1.strafeDown(); }
        if(keypress=='d') {player1.strafeRight(); }
        //cout<<"K"<<keypress<<endl;
    }



    return 0;
}

void mouseEventInGame(int event, int x, int y, int flags, void *param)
{
    using namespace cv;
    gameGraphics *cellptr = (gameGraphics*) param;

    if((event==EVENT_LBUTTONDOWN) || ((event==EVENT_MOUSEMOVE)&&(flags==EVENT_FLAG_LBUTTON)) )
    {
        cellptr->setGridLoc(cellptr->pixToGrid(y,x));
        cellptr->fillCell(0,0,255);
    }

    if(event == cv::EVENT_MOUSEMOVE)
    {
        //cellptr->drawPoint(0,255,255, cellptr->toDeCartes(cellptr->pixToGrid(y,x)));
        //cellptr->fillCell(0,255,255);
        player1.setPosition(cellptr->toDeCartes(cellptr->pixToGrid(y,x)));
    }

    if((event==EVENT_RBUTTONDOWN) || ((event==EVENT_MOUSEMOVE)&&(flags==EVENT_FLAG_RBUTTON)))
    {
        cellptr->setGridLoc(cellptr->pixToGrid(y,x));
        cellptr->fillCell(255,255,255);
    }
}
