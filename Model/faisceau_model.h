#pragma once
#include <QPoint>
#include <coordonnee.h>
#include <data_model.h>
#include <pile_model.h>
#include <vector>

class faisceau_model
{
private:
    QPoint topLeft;
    QPoint botRight;

    data_model Data;
    pile_model *p_Piles;

public:
    faisceau_model();
    faisceau_model(pile_model *pile, QPoint tl, QPoint br);

    void setFaisceau(QPoint pos1, QPoint pos2);

    QPoint getTopLeft() const;
    void setTopLeft(QPoint value);

    QPoint getBotRight() const;
    void setBotRight(QPoint value);

    data_model getData() const;
    void setData(const data_model &value);

    pile_model *getP_Piles() const;
    void setP_Piles(pile_model *value);

    void fillData();
};

