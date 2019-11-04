#include "data_view.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent) : QLabel( parent )
{

}

void Data_View::setData(std::vector<int> vec)
{
    data = vec;
    drawResults();
}

void Data_View::drawResults()
{
    int black[] = { 0,0,0 };
    int red[] = { 255,0,0 };

    CImg<float> image;
    image.assign(300,200,1,3);
    image.fill(255);

    image.draw_axes(0,data.size(),100,0.0f,black);

    //Calculs pour placer les points correctement
    int decalageX = image.width()/data.size();

    int oldX = 0;
    int oldY = 0;
    bool firstIteration = true;
    for (int y : data)
    {
        if (firstIteration)
        {
            oldY = calculPlacementY(image.height(),y);
            image.draw_point(oldX,oldY,red,1);
            firstIteration = false;
        }
        else
        {
            int newX = oldX+decalageX;
            int newY = calculPlacementY(image.height(),y);
            image.draw_line(oldX,oldY,newX,newY,red);
            oldX = newX;
            oldY = newY;
        }
    }

    image.save_bmp(pathToResult.c_str());

    QPixmap pm(pathToResult.c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}

int Data_View::calculPlacementY(int imageHeight, int y)
{
    return imageHeight - ( y*100/255 );
}
