#include <QPoint>
#include <cstdlib>
#include <iostream>
#include "gestionnaire_calques_model.h"
#include "analyse_model.h"
#include "dessin_model.h"

analyse_model::analyse_model() : areaIsSelected(false), userAreaIsSelected(false), isDataReady(false), columnAmount(30), linesAmount(30), errorMargin(5)
{}

void analyse_model::init(){
    areaIsSelected = false;
    userAreaIsSelected = false;
    isDataReady = false;
    currentArea = 0;

    results.clear();
}

std::string analyse_model::getResultDisplayPath() const { return pathOfResultsDisplay; }

std::vector<Resultat> analyse_model::getResults() const { return results; }

void analyse_model::processResults(CImgList<float> allPictures, int whiteValue, gestionnaire_calque_model * gestionnaire)
{
    ///DEBUG TESTS
    //    columnAmount = 5;
    //    linesAmount = 5;
    /////////////////

    results.clear();
    gestionnaire->reinitPertinenceCalque();

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

            int pertinence = processLocalResults(allPictures,pos1,pos2,whiteValue,false);

            //On créer un rond en fonction de l'analyse
            if (pertinence>1)
                gestionnaire->manageNewAnalyse(pertinence, pos1, pos2);

            oldY = nextY;
        }

        oldY = 0;
        oldX = nextX;
    }

    //Dans le cas de l'analyse global, on part de tout en haut à gauche
    QPoint posInit(0,0);
    //Dessin du quadrillage à la fin pour recouvrir l'ensemble après qu'on ai fait des carrés verts de pertinence
    gestionnaire->updateQuadrillage(columnAmount,linesAmount);

    std::cout << "ETUDE TOTALE TERMINEE" << std::endl;

    isDataReady = true;
}

void analyse_model::processResultsWithCropsVERSIONDEUX(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight, gestionnaire_calque_model * gestionnaire)
{
    int x1 = pos1.x() * allPictures[0].width() / labelWidth;
    int y1 = pos1.y() * allPictures[0].height() / labelHeight;
    int x2 = pos2.x() * allPictures[0].width() / labelWidth;
    int y2 = pos2.y() * allPictures[0].height() / labelHeight;

    //Positions de l'analyse en haut à gauche et en bas à droite
    QPoint departAnalyseHautGauche(x1,y1);
    QPoint finAnalyseBasDroite(x2,y2);

    /////DEBUG
    //    columnAmount = 5;
    //    linesAmount = 5;
    //////

    userResults.clear();

    int largeurImage = abs(departAnalyseHautGauche.x()-finAnalyseBasDroite.x());
    int hauteurImage = abs(departAnalyseHautGauche.y()-finAnalyseBasDroite.y());
    gestionnaire->reinitUserPertinenceCalque(largeurImage,hauteurImage);

    //Calcul de la taille de chaque ligne et colonne
    float xSeparateurFloat = (float)largeurImage / (float)columnAmount;
    float ySeparateurFloat = (float)hauteurImage / (float)linesAmount;

    int xSeparation = (int)xSeparateurFloat;
    int ySeparation = (int)ySeparateurFloat;

    int oldX = departAnalyseHautGauche.x();
    int oldY = departAnalyseHautGauche.y();

    for (int i=1; i<=columnAmount; i++)
    {
        int nextX = oldX + xSeparation;
        if (i == columnAmount)
            nextX = departAnalyseHautGauche.x()+largeurImage;

        for (int j=1; j<=linesAmount; j++)
        {
            int nextY = oldY + ySeparation;
            if (j == linesAmount)
                nextY = departAnalyseHautGauche.y()+hauteurImage;

            QPoint pos1(oldX,oldY);
            QPoint pos2(nextX,nextY);

            int pertinence = processLocalResults(allPictures,pos1,pos2,whiteValue,true);

            //On créer un rond en fonction de l'analyse
            if (pertinence>1)
            {
                //Les valeurs de point sont celles de l'image complète. Celles du calque commencent à zéro.
                //Il faut donc modifier les points pour les adapter au calque.
                pos1.setX(pos1.x()-departAnalyseHautGauche.x());
                pos1.setY(pos1.y()-departAnalyseHautGauche.y());
                pos2.setX(pos2.x()-departAnalyseHautGauche.x());
                pos2.setY(pos2.y()-departAnalyseHautGauche.y());

                gestionnaire->manageNewUserAnalyse(pertinence, pos1, pos2);
            }

            oldY = nextY;
        }

        oldY = departAnalyseHautGauche.y();
        oldX = nextX;
    }

    //Dessin du quadrillage à la fin pour recouvrir l'ensemble après qu'on a fait des carrés verts de pertinence
    gestionnaire->updateUserQuadrillage(columnAmount,linesAmount);

    isDataReady = true;
    std::cout << "ETUDE CROP TERMINEE" << std::endl;
}

int analyse_model::processLocalResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, bool isUserAnalysis)
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

    int pertinence = calculPertinence(localResult.getResults(), whiteValue);

    localResult.setPertinence(pertinence);

    if (isUserAnalysis)
    {
        userResults.push_back(localResult);
        //Génération du graphique associé au résultat
        createResultsDisplay(userResults.size()-1,allPictures.size(),whiteValue,true);
    }
    else
    {
        results.push_back(localResult);
        //Génération du graphique associé au résultat
        createResultsDisplay(results.size()-1,allPictures.size(),whiteValue,false);
    }

    return pertinence;
}

int analyse_model::calculPertinence(std::vector<float> data, int whiteValue)
{
    //Calcul de la pertinence de la zone
    int pertinence = 0;
    int origineVariation;
    bool graphMontant = false;
    for (unsigned int i=0; i<data.size(); i++)
    {
        int currentValue = data[i];

        //Enregistrement de la valeur initiale du graph
        if (i==0)
        {
            //Si la valeur est une valeur que l'on veut analyse on la prend en compte
            if (currentValue >= whiteValue)
                origineVariation = currentValue;
            //Sinon on prend la valeur minimale d'étude, qui servira si on passe au dessus du seuil plus tard
            else
                origineVariation = whiteValue;
        }
        else
        {
            // On ne fait des études que si on a une valeur supérieur au seuil
            if (currentValue >= whiteValue)
            {
                if (i==1)
                {
                    if (origineVariation < currentValue)
                        graphMontant = true;
                }
                else
                {
                    int previousValue = data[i-1];
                    //Le graph montait et ça change de sens
                    if (graphMontant && currentValue<previousValue)
                    {
                        int diff = abs(origineVariation-currentValue);
                        if (diff > errorMargin)
                            pertinence++;
                        origineVariation = previousValue;
                        graphMontant = false;
                    }
                    if (!graphMontant && currentValue>previousValue)
                    {
                        int diff = abs(origineVariation-currentValue);
                        if (diff > errorMargin)
                            pertinence++;
                        origineVariation = previousValue;
                        graphMontant = true;
                    }
                    if (i == data.size()-1 || currentValue == whiteValue)
                    {
                        int diff = abs(origineVariation-currentValue);
                        if (diff > errorMargin)
                            pertinence++;
                    }
                }
            }
        }
    }

    return pertinence;
}

int analyse_model::analyseForWhiteValue(CImg<float> middleImage)
{
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

    cimg_forXY(middleImage,x,y) {
        //Niveau de gris du pixel en cours
        int niveauNuance = (float)middleImage(x,y,0,0);

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
    return mediane;
}

void analyse_model::createResultsDisplay(int index, int imagesSize, int whiteValue, bool isUserAnalysis)
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


    if (isUserAnalysis)
    {
        for (int y : userResults[index].getResults())
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
    }
    else
    {
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
    }

    image.draw_text(10,hauteurAbscisse-15,abscisseText.c_str(),blue,white,1);

    //TODO Separator
    std::string chemin;
    if (isUserAnalysis)
        chemin = pathOfResultsStorage + "/user/" + std::to_string(index) + ".bmp";
    else
        chemin = pathOfResultsStorage + std::to_string(index) + ".bmp";

    image.save_bmp(chemin.c_str());
    isDataReady = true;
}


//void analyse_model::createCropResultsDisplay(Resultat result, unsigned int imagesSize, int whiteValue)
//{
//    int black[] = { 0,0,0 };
//    int white[] = { 255,255,255 };
//    int blue[] = { 0,0,255 };
//    int red[] = { 255,0,0 };
//    float valeurMediane = whiteValue * 100 / 255;
//    float valMaxGraph = 100-valeurMediane;
//    float valMinGraph = (100-valMaxGraph) * -1;

//    CImg<float> image;
//    image.assign(300,200,1,3);
//    image.fill(255);


//    int hauteurAbscisse = image.height() - image.height() * valeurMediane/100;
//    std::string val = std::to_string(valeurMediane);
//    std::string abscisseText;
//    if (valeurMediane < 10)
//        abscisseText = val.substr(0,1);
//    else
//        abscisseText = val.substr(0,2) + "%";
//    abscisseText.append("%");

//    std::string ordonnee = " Variation % Nuance";
//    image.draw_text(20,0,ordonnee.c_str(),black,white,1);
//    image.draw_axes(0,imagesSize-1,valMaxGraph,valMinGraph,black,1,-60,-60,1);

//    //Calculs pour placer les points correctement
//    int decalageX = image.width()/imagesSize;

//    int oldX = 0;
//    int oldY = 0;
//    bool firstIteration = true;


//    for (int y : result.getResults())
//    {
//        if (firstIteration)
//        {
//            oldY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);
//            image.draw_point(oldX,oldY,red,1);
//            firstIteration = false;
//        }
//        else
//        {
//            int newX = oldX+decalageX;
//            int newY = calculPlacementY(image.height(),y, valeurMediane, hauteurAbscisse);

//            image.draw_line(oldX,oldY,newX,newY,red);
//            oldX = newX;
//            oldY = newY;
//        }
//    }

//    image.draw_text(10,hauteurAbscisse-15,abscisseText.c_str(),blue,white,1);

//    image.save_bmp(pathOfResultsDisplay.c_str());
//    isDataReady = true;
//}

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
