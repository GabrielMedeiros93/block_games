#include "gridGraphics.h"
#include "math.h"
#define CELL_LENGTH 20
using namespace cv;

gridGraphics::gridGraphics(Mat &image)
{
    //ctor
    img = image;
    cell_length = CELL_LENGTH;
    rows = (img.rows)/cell_length; cols = (img.cols)/cell_length;
    gridPoint.x = 1; gridPoint.y = 1;
    buf = new int*[rows+2];
    for(i=0;i<rows+2;i++) buf[i] = new int[cols+2];
    std::cout<<"\nThe size of the image is: "<<img.rows<<"x"<<img.cols<<"\n";
}

gridGraphics::gridGraphics(Mat &image, int cellLength)
{
    //ctor
    img = image;
    cell_length = cellLength;
    rows = (img.rows)/cell_length; cols = (img.cols)/cell_length;
    gridPoint.x = 1; gridPoint.y = 1;
    buf = new int*[rows+2];
    for(i=0;i<rows+2;i++) buf[i] = new int[cols+2];
    std::cout<<"\nThe size of the image is: "<<img.rows<<"x"<<img.cols<<"\n";
}

///Sets the image to be manipulated
void gridGraphics::setImage(cv::Mat &image)
{
    img = image;
}

cv::Point gridGraphics::pixToGrid(int pix_row, int pix_col)
{
    cv::Point pt((int)(pix_col/cell_length)+1,(int)(pix_row/cell_length)+1);
    return pt;
}

void gridGraphics::setGridLoc(int row, int col)
{
    gridPoint.x  = col;
    gridPoint.y  = row;
    cell_start.y = (gridPoint.y - 1)*cell_length;
    cell_start.x = (gridPoint.x - 1)*cell_length;
    cell_end.y   = (gridPoint.y)*cell_length;
    cell_end.x   = (gridPoint.x)*cell_length;
}

void gridGraphics::setGridLoc(cv::Point gridLoc)
{
    gridPoint = gridLoc;
    cell_start.y = (gridPoint.y - 1)*cell_length;
    cell_start.x = (gridPoint.x - 1)*cell_length;
    cell_end.y   = (gridPoint.y)*cell_length;
    cell_end.x   = (gridPoint.x)*cell_length;
}

void gridGraphics::fillCell(int R, int G, int B)
{
    i=0; j=0;
    for(i=cell_start.y+1; i<cell_end.y; i++)
    {
        for(j=cell_start.x+1; j<cell_end.x; j++)
        {
            img.at<cv::Vec3b>(i,j)[0] = B;
            img.at<cv::Vec3b>(i,j)[1] = G;
            img.at<cv::Vec3b>(i,j)[2] = R;
        }
    }
}

void gridGraphics::fillTargetCell(int R, int G, int B, cv::Point gridLoc)
{
    i=0; j=0;
    for(i=(gridLoc.y - 1)*cell_length+1; i<(gridLoc.y)*cell_length; i++)
    {
        for(j=(gridLoc.x - 1)*cell_length+1; j<(gridLoc.x)*cell_length; j++)
        {
            img.at<cv::Vec3b>(i,j)[0] = B;
            img.at<cv::Vec3b>(i,j)[1] = G;
            img.at<cv::Vec3b>(i,j)[2] = R;
        }
    }

}

void gridGraphics::fillAllCells(int R, int G, int B)
{
    int i,j;
    for(i=1;i<=getRows();i++)
    {
        for(j=1;j<=getCols();j++)
        {
            fillTargetCell(R,G,B, Point(j,i));
        }
    }
}

bool gridGraphics::cellIsAlive(cv::Point gridLoc)
{

    if((img.at<cv::Vec3b>(((gridLoc.y-1)*cell_length)+2,((gridLoc.x-1)*cell_length)+2)[0]==255)&&
        (img.at<cv::Vec3b>(((gridLoc.y-1)*cell_length)+2,((gridLoc.x-1)*cell_length)+2)[1]==0)&&
        (img.at<cv::Vec3b>(((gridLoc.y-1)*cell_length)+2,((gridLoc.x-1)*cell_length)+2)[2]==0)) return true;
        else return false;
}

int gridGraphics::neighbourCount(cv::Point gridLoc)
{
    int lifeCount=0;
    cv::Point loc = gridLoc + cv::Point(-1,-1);

    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(0,1);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(0,1);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(1,0);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(1,0);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(0,-1);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(0,-1);
    if(cellIsAlive(loc)) lifeCount++; loc += cv::Point(-1,0);
    if(cellIsAlive(loc)) lifeCount++;

    return lifeCount;
}

void gridGraphics::clearImgBuf()
{
    i=0; j=0;
    for(i=0; i<rows+2; i++)
    {
        for(j=0; j<cols+2; j++)
        {
            buf[i][j]=0;
        }
    }
}

int gridGraphics::getRows()
{
    return rows;
}

int gridGraphics::getCols()
{
    return cols;
}

double gridGraphics::getDirectDistance(Point gridPoint1, Point gridPoint2)
{
    return sqrt(pow((gridPoint1.x - gridPoint2.x),2) + pow((gridPoint1.y - gridPoint2.y),2));
}

gridGraphics::~gridGraphics()
{
    //dtor
    ///Nothing to do here.
}
