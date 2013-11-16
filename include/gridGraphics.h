#ifndef GRIDGRAPHICS_H
#define GRIDGRAPHICS_H
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define CELL_LENGTH 20


class gridGraphics
{

    public:
        ///Constructor
        gridGraphics(cv::Mat &image);
        gridGraphics(cv::Mat &image, int cellLength);

        ///Sets the image to be manipulated
        void setImage(cv::Mat &image);

        ///convert from pixel to grid coordinates
        cv::Point pixToGrid(int pix_row, int pix_col);

        ///Set the grid location
        void setGridLoc(int row, int col);
        void setGridLoc(cv::Point gridLoc);

        ///Fill a cell with specified color
        void fillCell(int R, int G, int B);
        void fillTargetCell(int R, int G, int B, cv::Point gridLoc);
        void fillAllCells(int R, int G, int B);

        ///Check if cell is alive
        bool cellIsAlive(cv::Point gridLoc);
        ///Check if neighbours are nice
        int neighbourCount(cv::Point gridLoc);
        ///Step through simulation
        void simUpdate();
        ///Clear imgbuf
        void clearImgBuf();
        int getRows();
        int getCols();

        ///Get distance between two grid points
        double getDirectDistance(cv::Point gridPoint1, cv::Point gridPoint2);

        ///This variable is an array that is supposed to store the
        ///current state of each cell. A point in the array stores 1 if
        ///the grid point indexed by its location is alive and stores 0
        ///if the grid point is dead.
        int **buf;


        virtual ~gridGraphics();
    protected:
    private:
        int rows, cols,i,j;
        cv::Mat img;
        int cell_length;
        cv::Point gridPoint;
        cv::Point cell_start;
        cv::Point cell_end;
};

#endif // GRIDGRAPHICS_H
