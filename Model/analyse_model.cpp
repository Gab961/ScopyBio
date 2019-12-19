#include <QPoint>
#include <cstdlib>
#include <iostream>
#include "gestionnaire_calques_model.h"
#include "analyse_model.h"
#include "dessin_model.h"

analyse_model::analyse_model() : areaIsSelected(false), userAreaIsSelected(false), isDataReady(false), columnAmount(30), linesAmount(30)
{}

void analyse_model::init(){
    areaIsSelected = false;
    userAreaIsSelected = false;
    isDataReady = true;
    currentArea = 0;

    results.clear();
}

std::string analyse_model::getResultDisplayPath() const { return pathOfResultsDisplay; }

std::vector<Resultat> analyse_model::getResults() const { return results; }

void analyse_model::processResults(CImgList<float> allPictures, int whiteValue, gestionnaire_calque_model * gestionnaire)
{
    ///DEBUG TESTS
    columnAmount = 5;
    linesAmount = 5;
    /////////////////

    results.clear();

    //Dessin du quadrillage
    gestionnaire->updateQuadrillage(columnAmount,linesAmount);

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
            int milieuX = oldX+abs(oldX-nextX)/2;
            int milieuY = oldY+abs(oldY-nextY)/2;
            QPoint posMid(milieuX,milieuY);
            //            std::cout << "Analyse de " << pos1.x() << "," << pos1.y() << " à " << pos2.x() << "," << pos2.y() << std::endl;

            int pertinence = processLocalResults(allPictures,pos1,pos2,whiteValue);
            //On créer un rond en fonction de l'analyse
            if (pertinence>0)
                gestionnaire->manageNewAnalyse(pertinence, pos1, pos2);

            oldY = nextY;
        }

        oldY = 0;
        oldX = nextX;
    }

    /*
    for (unsigned int i=0; i<results.size(); i++)
    {
        for (unsigned int j=0; j<results[i].getResults().size(); j++)
        {
            std::cout << results[i].getResults()[j] << " | ";
        }
        std::cout << std::endl;
        std::cout << "------------------" << std::endl;
    }
    */
}

int analyse_model::processLocalResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue)
{
    Resultat localResult;

    //Gestion si les points ne sont pas bien positionnés (ne devrait pas arriver)
    if (pos1.x() < pos2.x())
    {
        localResult.setTopLeftPoint(pos1);
        localResult.setBottomRightPoint(pos2);
    }
    else
    {
        localResult.setTopLeftPoint(pos2);
        localResult.setBottomRightPoint(pos1);
    }

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

        localResult.addResult(totalNuance/nombrePixels);
    }


    //Calcul de la pertinence de la zone
    int pertinence = 0;
    bool sousLeWhite;
    for (unsigned int i=0; i<localResult.getResults().size(); i++)
    {
        if (i==0)
        {
            if (localResult.getResultAtIndex(i)<whiteValue)
                sousLeWhite = true;
            else
                sousLeWhite = false;
        }
        else
        {
            if (sousLeWhite == false && localResult.getResultAtIndex(i)<=whiteValue)
            {
                sousLeWhite = true;
                pertinence++;
            }
            if (sousLeWhite == true && localResult.getResultAtIndex(i)>=whiteValue)
            {
                sousLeWhite = false;
                pertinence++;
            }
        }
    }

    localResult.setPertinence(pertinence);

    results.push_back(localResult);

    //Génération du graphique associé au résultat
    createResultsDisplay(results.size()-1,allPictures.size(),whiteValue);

    return pertinence;
}

void analyse_model::processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight)
{
    Resultat localResult;

    int x1 = pos1.x() * allPictures[0].width() / labelWidth;
    int y1 = pos1.y() * allPictures[0].height() / labelHeight;
    int x2 = pos2.x() * allPictures[0].width() / labelWidth;
    int y2 = pos2.y() * allPictures[0].height() / labelHeight;

    QPoint picturePos1(x1,y1);
    QPoint picturePos2(x2,y2);
    localResult.setTopLeftPoint(picturePos1);
    localResult.setBottomRightPoint(picturePos2);

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

        localResult.addResult(totalNuance/nombrePixels);
    }

    createCropResultsDisplay(localResult, allPictures.size(), whiteValue);
}

//TODO DETERMINER LA MEILLEURE APPROCHE POUR LE BLANC
int analyse_model::analyseForWhiteValue()
{
    CImg<float> flattenImage;
    flattenImage.load_bmp("tmp/flatten.bmp");

    /** MOYENNE
    float totalNuance = 0;
    float nombrePixel = flattenImage.width() * flattenImage.height();
    */

    /** BLANC MAX
    int blancMax = 0;
    */

    /** MEDIANE */
    int blancMax = 0;
    int noirMax = 255;

    cimg_forXY(flattenImage,x,y) {
        //Niveau de gris du pixel en cours
        int niveauNuance = (float)flattenImage(x,y,0,0);

        /** CALCUL DE LA MOYENNE
        totalNuance += niveauNuance;
        */


        /** CALCUL DU BLANC MAXIMAL*
        if (blancMax < niveauNuance)
            blancMax = niveauNuance;
        */

        /** CALCUL DE LA MEDIANE */
        if (blancMax < niveauNuance)
            blancMax = niveauNuance;


        if (noirMax > niveauNuance)
            noirMax = niveauNuance;
    }

    /** Suite moyenne
    float whiteFloat = totalNuance/nombrePixel;
    int white = (int)whiteFloat;
    return white;
    */

    /** Suite blancMax
    return blancMax-40;
    */

    /** Mediane */
    int mediane = (blancMax + noirMax) / 2;
    //Test random pour trouver une valeur bien
    return mediane + 30;
}

void analyse_model::createResultsDisplay(int index, int imagesSize, int whiteValue)
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


    for (int y : results[index].getResults())
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

    std::string chemin = pathOfResultsStorage + std::to_string(index) + ".bmp";

    image.save_bmp(chemin.c_str());
    isDataReady = true;
}

void analyse_model::createCropResultsDisplay(Resultat result, unsigned int imagesSize, int whiteValue)
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


    for (int y : result.getResults())
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
    float valeurDepuisMedian = percentageY-(float)valeurMediane;
    float res = hauteurAbscisse - valeurDepuisMedian*imageHeight/100;
    return (int)res;
}

int analyse_model::getItemAtPoint(int imagesAmount, int posX, int labelWidth)
{
    //Pixels entre chaque élément image sur le graph
    float xSpaceFloat = (float)labelWidth / (float)imagesAmount;
    float res = (float)posX/xSpaceFloat;
    return (int)res;
}

void analyse_model::getDataFromArea(QPoint area, int labelWidth, int labelHeight, int imageWidth, int imageHeight, CImg<float> currentImage, dessin_model *dessin) {

    int x = area.x() * imageWidth / labelWidth;
    int y = area.y() * imageHeight / labelHeight;

    for(unsigned int i = 0; i < results.size(); i++) {
        if (results[i].getTopLeftPoint().x() <= x
                && results[i].getTopLeftPoint().y() <= y
                && results[i].getBottomRightPoint().x() > x
                && results[i].getBottomRightPoint().y() > y) {

            currentArea = i;
            areaIsSelected = true;
            dessin->saveZoomFromArea(results[currentArea].getTopLeftPoint(), results[currentArea].getBottomRightPoint(), currentImage);
            std::string graphFromArea = pathOfResultsStorage + std::to_string(i) + ".bmp";
            CImg<float> graphImg;
            graphImg.load_bmp(graphFromArea.c_str());
            graphImg.save_bmp(pathOfResultsDisplay.c_str());
        }
    }
}


bool analyse_model::dataReady() { return isDataReady; }
void analyse_model::setColumnAmount(int newColumn) { columnAmount = newColumn; }
int analyse_model::getColumnAmount() { return columnAmount; }
void analyse_model::setLinesAmount(int newLine) { linesAmount = newLine; }
int analyse_model::getLinesAmount() { return linesAmount; }
bool analyse_model::getAreaIsSelected() { return areaIsSelected; }
void analyse_model::setAreaIsSelected(bool newValue) { areaIsSelected = newValue; }
bool analyse_model::getUserAreaIsSelected() { return userAreaIsSelected; }
void analyse_model::setUserAreaIsSelected(bool newValue) { userAreaIsSelected = newValue; }

void analyse_model::setResults(const std::vector<Resultat> &value)
{
    results = value;
}
