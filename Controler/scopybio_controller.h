#ifndef SCOPYBIO_CONTROLLER_H
#define SCOPYBIO_CONTROLLER_H

#include <iostream>

class ScopyBio_Controller
{
private:
    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image

public:
    ScopyBio_Controller();

    void setPercentOfBlack(float black);

    void putColorGreen();
    void putColorWhite();

    void displayAnnotation();
    void hideAnnotation();

    void displayContour();
    void hideContour();


};

#endif // SCOPYBIO_CONTROLLER_H
