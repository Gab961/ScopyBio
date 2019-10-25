#ifndef SCOPYBIO_CONTROLLER_H
#define SCOPYBIO_CONTROLLER_H

#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>

class ScopyBio_Controller
{
private:
    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image

public:
    ScopyBio_Controller();

    void setPercentOfBlack(float black); //TODO

    void putColorGreen();//TODO
    void putColorWhite();//TODO

    void displayAnnotation();//TODO
    void hideAnnotation();//TODO

    void displayContour();//TODO
    void hideContour();//TODO


};

#endif // SCOPYBIO_CONTROLLER_H
