#include <QPoint>
#include <iostream>
#include "data_model.h"

data_model::data_model()
{

}

std::string data_model::getResultDisplayPath() const { return pathOfResultsDisplay; }

std::vector<int> data_model::getResults() const { return results; }


void data_model::processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    results.clear();

    int x1 = pos1.x() * allPictures[0].width() / labelWidth;
    int y1 = pos1.y() * allPictures[0].height() / labelHeight;
    int x2 = pos2.x() * allPictures[0].width() / labelWidth;
    int y2 = pos2.y() * allPictures[0].height() / labelHeight;

    for(CImg<float> image : allPictures)
    {
        CImg<float> zoom = image.get_crop(x1+1,y1+1,0,x2-1,y2-1,0);
        int nombrePixels = 0;
        int totalNuance = 0;
        int niveauDeBlancMaximal = 0;
        int niveauDeNoirMaximal = 255;

        //Pour chaque pixel de l'image
        cimg_forXY(zoom,x,y) {
            //Niveau de gris du pixel en cours
            int niveauNuance = (int)zoom(x,y,0,0);


            //TODO Déterminer les actions à faire
            nombrePixels++;
            totalNuance += niveauNuance;

            if (niveauDeBlancMaximal < niveauNuance)
                niveauDeBlancMaximal = niveauNuance;

            if (niveauDeNoirMaximal > niveauNuance)
                niveauDeNoirMaximal = niveauNuance;
        }

        //TODO là on renvoie que la moyenne pour le moment
        results.push_back(totalNuance/nombrePixels);
    }

    createResultsDisplay();
}

void data_model::processResults(CImgList<float> allPictures)
{
    results.clear();
    for(CImg<float> image : allPictures)
    {
        int nombrePixels = 0;
        int totalNuance = 0;
        int niveauDeBlancMaximal = 0;
        int niveauDeNoirMaximal = 255;

        //Pour chaque pixel de l'image
        cimg_forXY(image,x,y) {
            //Niveau de gris du pixel en cours
            int niveauNuance = (int)image(x,y,0,0);


            //TODO Déterminer les actions à faire
            nombrePixels++;
            totalNuance += niveauNuance;

            if (niveauDeBlancMaximal < niveauNuance)
                niveauDeBlancMaximal = niveauNuance;

            if (niveauDeNoirMaximal > niveauNuance)
                niveauDeNoirMaximal = niveauNuance;
        }

        //TODO là on renvoie que la moyenne pour le moment
        results.push_back(totalNuance/nombrePixels);
    }

    createResultsDisplay();
}


void data_model::createResultsDisplay()
{
        int black[] = { 0,0,0 };
        int red[] = { 255,0,0 };

        CImg<float> image;
        image.assign(300,200,1,3);
        image.fill(255);

        image.draw_axes(0,results.size(),100,0.0f,black);

        //Calculs pour placer les points correctement
        int decalageX = image.width()/results.size();

        int oldX = 0;
        int oldY = 0;
        bool firstIteration = true;
        for (int y : results)
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

        image.save_bmp(pathOfResultsDisplay.c_str());
}

int data_model::calculPlacementY(int imageHeight, int y)
{
    int percentageValue = y*100/255;
    return imageHeight - percentageValue*imageHeight/100;
}
