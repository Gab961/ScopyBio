#include "faisceau_model.h"

QPoint faisceau_model::getTopLeft() const
{
    return topLeft;
}

void faisceau_model::setTopLeft(QPoint value)
{
    topLeft = value;
}

QPoint faisceau_model::getBotRight() const
{
    return botRight;
}

void faisceau_model::setBotRight(QPoint value)
{
    botRight = value;
}

pile_model *faisceau_model::getP_Piles() const
{
    return p_Piles;
}

void faisceau_model::setP_Piles(pile_model *value)
{
    p_Piles = value;
}

void faisceau_model::fillData()
{

}

faisceau_model::faisceau_model() : faisceauIsSet(false)
{

}

void faisceau_model::setFaisceau(QPoint pos1, QPoint pos2)
{
    if (pos1.x() > pos2.x())
    {
        setTopLeft(pos2);
        setBotRight(pos1);
    }
    else
    {
        setTopLeft(pos1);
        setBotRight(pos2);
    }

    faisceauIsSet = true;
}

bool faisceau_model::faisceauExist()
{
    return faisceauIsSet;
}

faisceau_model::faisceau_model(pile_model *pile , QPoint tl, QPoint br){
    topLeft = tl;
    botRight = br;

    faisceauIsSet = true;

    p_Piles = pile;
}

