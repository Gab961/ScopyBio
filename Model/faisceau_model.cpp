#include "faisceau_model.h"

coordonnee faisceau_model::getTopLeft() const
{
    return topLeft;
}

void faisceau_model::setTopLeft(const coordonnee &value)
{
    topLeft = value;
}

coordonnee faisceau_model::getBotRight() const
{
    return botRight;
}

void faisceau_model::setBotRight(const coordonnee &value)
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

faisceau_model::faisceau_model()
{

}

faisceau_model::faisceau_model(pile_model *pile , coordonnee tl, coordonnee br){
    topLeft = tl;
    botRight = br;

    p_Piles = pile;
}

