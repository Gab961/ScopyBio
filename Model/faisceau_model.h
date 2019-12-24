#pragma once
#include <QPoint>
#include <analyse_model.h>
#include <pile_model.h>
#include <vector>

class faisceau_model
{
private:
    QPoint topLeft;
    QPoint botRight;
    QPoint scaledTopLeft;
    QPoint scaledBotRight;

    analyse_model Data;
    pile_model *p_Piles;

    bool faisceauActive;

public:
    faisceau_model();
    faisceau_model(pile_model *pile, QPoint tl, QPoint br);

    void setFaisceau(QPoint pos1, QPoint pos2, int pictureWidth, int pictureHeight, int labelWidth, int labelHeight);

    bool faisceauIsActive();
    void setFaisceauInactive();

    QPoint getTopLeft() const;
    void setTopLeft(QPoint value);

    QPoint getBotRight() const;
    void setBotRight(QPoint value);

    QPoint getScaledTopLeft() const;
    void setScaledTopLeft(int tl, int br);
    QPoint getScaledBotRight() const;
    void setScaledBotRight(int tl, int br);

    analyse_model getData() const;
    void setData(const analyse_model &value);

    pile_model *getP_Piles() const;
    void setP_Piles(pile_model *value);

    void fillData();
};

