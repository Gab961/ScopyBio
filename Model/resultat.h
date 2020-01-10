#pragma once
#include <vector>

class QPoint;

/**
    * @brief The Resultat class save all datas of analysis
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

    /**
     * @brief addResult add a result to the list
     * @param newResult the average white value of the beam
     */
    void addResult(float newResult);
    std::vector<QPoint> coordonees;
    std::vector<float> getResults();

    /**
     * @brief getResultAtIndex get the result at index
     * @param index the id of the image
     * @return the average white value to one beam
     */
    float getResultAtIndex(int index);
    void setResults(const std::vector<float> &value);
};
