#include <QPoint>
#include <iostream>
#include "gestionnaire_calques_model.h"
#include "analyse_model.h"

analyse_model::analyse_model() : isDataReady(false)
{}

std::string analyse_model::getResultDisplayPath() const { return pathOfResultsDisplay; }

std::vector<std::vector<float>> analyse_model::getResults() const { return results; }

void analyse_model::processResults(CImgList<float> allPictures, int whiteValue, gestionnaire_calque_model * gestionnaire)
{
    whiteValue = 60;
    std::cout << "White = " << whiteValue << std::endl;

    results.clear();

    int largeurImage = allPictures[0].width();
    int hauteurImage = allPictures[0].height();

    //Calcul de la taille de chaque ligne et colonne
    float xSeparateurFloat = (float)largeurImage / (float)columnAmount;
    float ySeparateurFloat = (float)hauteurImage / (float)linesAmount;

    int xSeparation = (int)xSeparateurFloat;
    int ySeparation = (int)ySeparateurFloat;

    int oldX = 0;
    int oldY = 0;

    for (int i=1; i<=columnAmount; i++)
    {
        int nextX = oldX + xSeparation;
        if (i == columnAmount)
            nextX = largeurImage;

        for (int j=1; j<=linesAmount; j++)
        {
            int nextY = oldY + ySeparation;
            if (j == linesAmount)
                nextY = hauteurImage;

            QPoint pos1(oldX,oldY);
            QPoint pos2(nextX,nextY);
            QPoint milieu(oldX+(oldX-nextX),oldY+(oldY-nextY));
            //            std::cout << "Analyse de " << pos1.x() << "," << pos1.y() << " à " << pos2.x() << "," << pos2.y() << std::endl;

            int pertinence = processLocalResults(allPictures,pos1,pos2,whiteValue);
            //On créer un rond en fonction de l'analyse
            if (pertinence>0)
                gestionnaire->manageNewAnalyse(pertinence, milieu);

            oldY = nextY;
        }

        oldY = 0;
        oldX = nextX;
    }

    //On demande au gestionnaire de calque de mettre à jour le calque des résultats (cercles)
}

int analyse_model::processLocalResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue)
{
    std::vector<float> localResult;

    for(CImg<float> image : allPictures)
    {
        CImg<float> zoom = image.get_crop(pos1.x(),pos1.y(),0,pos2.x(),pos2.y(),0);
        float nombrePixels = zoom.width() * zoom.height();
        float totalNuance = 0;
        int niveauDeBlancMaximal = 0;
        int niveauDeNoirMaximal = 255;

        //Pour chaque pixel de l'image
        cimg_forXY(zoom,x,y) {
            //Niveau de gris du pixel en cours
            int niveauNuance = (float)zoom(x,y,0,0);

            totalNuance += niveauNuance;

            if (niveauDeBlancMaximal < niveauNuance)
                niveauDeBlancMaximal = niveauNuance;

            if (niveauDeNoirMaximal > niveauNuance)
                niveauDeNoirMaximal = niveauNuance;
        }

        localResult.push_back(totalNuance/nombrePixels);
    }


    //Calcul de la pertinence de la zone
    int pertinence = 0;
    bool sousLeWhite;
    for (unsigned int i=0; i<localResult.size(); i++)
    {
        if (i==0)
        {
            if (localResult[i]<whiteValue)
                sousLeWhite = true;
            else
                sousLeWhite = false;
        }
        else
        {
            if (sousLeWhite == false && localResult[i]<=whiteValue)
            {
                sousLeWhite = true;
                pertinence++;
            }
            if (sousLeWhite == true && localResult[i]>=whiteValue)
            {
                sousLeWhite = false;
                pertinence++;
            }
        }
    }

    results.push_back(localResult);

    return pertinence;
}


//TODO a voir si on l'utilise encore
void analyse_model::processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight)
{
    std::vector<float> localResult;

    int x1 = pos1.x() * allPictures[0].width() / labelWidth;
    int y1 = pos1.y() * allPictures[0].height() / labelHeight;
    int x2 = pos2.x() * allPictures[0].width() / labelWidth;
    int y2 = pos2.y() * allPictures[0].height() / labelHeight;

    for(CImg<float> image : allPictures)
    {
        CImg<float> zoom = image.get_crop(x1+1,y1+1,0,x2-1,y2-1,0);
        float nombrePixels = zoom.width() * zoom.height();
        float totalNuance = 0;
        int niveauDeBlancMaximal = 0;
        int niveauDeNoirMaximal = 255;

        //Pour chaque pixel de l'image
        cimg_forXY(zoom,x,y) {
            //Niveau de gris du pixel en cours
            int niveauNuance = (float)zoom(x,y,0,0);

            totalNuance += niveauNuance;

            if (niveauDeBlancMaximal < niveauNuance)
                niveauDeBlancMaximal = niveauNuance;

            if (niveauDeNoirMaximal > niveauNuance)
                niveauDeNoirMaximal = niveauNuance;
        }

        localResult.push_back(totalNuance/nombrePixels);
    }

    results.push_back(localResult);

    //TODO Y a plus besoin de le faire
    //    createResultsDisplay(whiteValue);
}

/***************************************************************************/
void analyse_model::createResultsDisplayDEBUG(int index, int imagesSize, int whiteValue)
{
    int black[] = { 0,0,0 };
    int white[] = { 255,255,255 };
    int blue[] = { 0,0,255 };
    int red[] = { 255,0,0 };
    float valeurMediane = whiteValue * 100 / 255;
    float valMaxGraph = 100-valeurMediane;
    float valMinGraph = (100-valMaxGraph) * -1;

    CImg<float> image;
    image.assign(300,200,1,3);
    image.fill(255);


    int hauteurAbscisse = image.height() - image.height() * valeurMediane/100;
    std::string val = std::to_string(valeurMediane);
    std::string abscisseText;
    if (valeurMediane < 10)
        abscisseText = val.substr(0,1);
    else
        abscisseText = val.substr(0,2) + "%";
    abscisseText.append("%");

    std::string ordonnee = " Variation % Nuance";
    image.draw_text(20,0,ordonnee.c_str(),black,white,1);
    image.draw_axes(0,imagesSize-1,valMaxGraph,valMinGraph,black,1,-60,-60,1);

    //Calculs pour placer les points correctement
    int decalageX = image.width()/imagesSize;

    int oldX = 0;
    int oldY = 0;
    bool firstIteration = true;
    for (int y : results[index])
    {
        if (firstIteration)
        {
            oldY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);
            image.draw_point(oldX,oldY,red,1);
            firstIteration = false;
        }
        else
        {
            int newX = oldX+decalageX;
            int newY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);

            image.draw_line(oldX,oldY,newX,newY,red);
            oldX = newX;
            oldY = newY;
        }
    }

    image.draw_text(10,hauteurAbscisse-15,abscisseText.c_str(),blue,white,1);

    std::string chemin = pathOfResultsDisplayDEBUG + std::to_string(index) + ".bmp";
    image.save_bmp(chemin.c_str());
}
/*******************************************************************************/



void analyse_model::createResultsDisplay(int index, int whiteValue)
{
    int black[] = { 0,0,0 };
    int white[] = { 255,255,255 };
    int blue[] = { 0,0,255 };
    int red[] = { 255,0,0 };
    float valeurMediane = whiteValue * 100 / 255;
    float valMaxGraph = 100-valeurMediane;
    float valMinGraph = (100-valMaxGraph) * -1;

    CImg<float> image;
    image.assign(300,200,1,3);
    image.fill(255);


    int hauteurAbscisse = image.height() - image.height() * valeurMediane/100;
    std::string val = std::to_string(valeurMediane);
    std::string abscisseText;
    if (valeurMediane < 10)
        abscisseText = val.substr(0,1);
    else
        abscisseText = val.substr(0,2) + "%";
    abscisseText.append("%");

    std::string ordonnee = " Variation % Nuance";
    image.draw_text(20,0,ordonnee.c_str(),black,white,1);
    image.draw_axes(0,results.size()-1,valMaxGraph,valMinGraph,black,1,-60,-60,1);

    //Calculs pour placer les points correctement
    int decalageX = image.width()/results.size();

    int oldX = 0;
    int oldY = 0;
    bool firstIteration = true;
    for (int y : results[index])
    {
        if (firstIteration)
        {
            oldY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);
            image.draw_point(oldX,oldY,red,1);
            firstIteration = false;
        }
        else
        {
            int newX = oldX+decalageX;
            int newY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);

            image.draw_line(oldX,oldY,newX,newY,red);
            oldX = newX;
            oldY = newY;
        }
    }

    image.draw_text(10,hauteurAbscisse-15,abscisseText.c_str(),blue,white,1);

    image.save_bmp(pathOfResultsDisplay.c_str());
    isDataReady = true;
}

int analyse_model::calculPlacementY(int imageHeight, int y, int valeurMediane, int hauteurAbscisse)
{
    float percentageY = (float)y*100/255;
    //TODO faire le super calcul
    float valeurDepuisMedian = percentageY-(float)valeurMediane;
    float res = hauteurAbscisse - valeurDepuisMedian*imageHeight/100;
    return (int)res;
}


int analyse_model::getItemAtPoint(int posX, int labelWidth)
{
    int resultsAmount = results.size();
    //Pixels entre chaque élément du vecteur
    float xSpaceFloat = (float)labelWidth / (float)resultsAmount;
    float res = (float)posX/xSpaceFloat;
    return (int)res;
}


bool analyse_model::dataReady() { return isDataReady; }
