#pragma once
#include <vector>


class QPoint;

/**
    * @brief The Resultat class Contient toutes les données d'une analyse
    */
class Resultat {
    int pertinence;
    std::vector<float> results;

public:
    Resultat();

    void setPertinence(int newPertinence);
    int getPertinence();

    void setTopLeftPoint(QPoint pos);
    QPoint getTopLeftPoint();

    void setBottomRightPoint(QPoint pos);
    QPoint getBottomRightPoint();

    void setMiddlePoint(QPoint pos);
    QPoint getMiddlePoint();

    void addResult(float newResult);
    std::vector<QPoint> coordonees;
    std::vector<float> getResults();
    float getResultAtIndex(int index);
};
