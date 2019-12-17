#include "resultat.h"
#include <QPoint>

Resultat::Resultat()
{
    coordonees.reserve(3);
}

void Resultat::setPertinence(int newPertinence) { pertinence = newPertinence; }
int Resultat::getPertinence() { return pertinence; }

void Resultat::setTopLeftPoint(QPoint pos) { coordonees[0] = pos; }
QPoint Resultat::getTopLeftPoint() { return coordonees[0]; }

void Resultat::setBottomRightPoint(QPoint pos) { coordonees[1] = pos; }
QPoint Resultat::getBottomRightPoint() { return coordonees[1]; }

void Resultat::setMiddlePoint(QPoint pos) { coordonees[2] = pos; }
QPoint Resultat::getMiddlePoint() { return coordonees[2]; }

void Resultat::addResult(float newResult) { results.push_back(newResult); }
std::vector<float> Resultat::getResults() { return results; }
float Resultat::getResultAtIndex(int index) { return results[index]; }
