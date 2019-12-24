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

QPoint faisceau_model::getScaledTopLeft() const { return scaledTopLeft; }
QPoint faisceau_model::getScaledBotRight() const { return scaledBotRight; }
void faisceau_model::setScaledTopLeft(int tl, int br)
{
    scaledTopLeft.setX(tl);
    scaledTopLeft.setY(br);
}
void faisceau_model::setScaledBotRight(int tl, int br)
{
    scaledBotRight.setX(tl);
    scaledBotRight.setY(br);
}

faisceau_model::faisceau_model() : faisceauActive(false)
{

}

void faisceau_model::setFaisceau(QPoint pos1, QPoint pos2, int pictureWidth, int pictureHeight, int labelWidth, int labelHeight)
{
    int x1 = pos1.x() * pictureWidth / labelWidth;
    int y1 = pos1.y() * pictureHeight / labelHeight;
    int x2 = pos2.x() * pictureWidth / labelWidth;
    int y2 = pos2.y() * pictureHeight/ labelHeight;

    if (pos1.x() > pos2.x())
    {
        setTopLeft(pos2);
        setBotRight(pos1);
        setScaledTopLeft(x2,y2);
        setScaledBotRight(x1,y1);
    }
    else
    {
        setTopLeft(pos1);
        setBotRight(pos2);
        setScaledBotRight(x2,y2);
        setScaledTopLeft(x1,y1);
    }

    std::cout << "SCALED" << std::endl;
    std::cout << "TopLeft: " << scaledTopLeft.x() << "x" << scaledTopLeft.y() << std::endl;
    std::cout << "BotRight: " << scaledBotRight.x() << "x" << scaledBotRight.y() << std::endl;

    faisceauActive = true;
}

bool faisceau_model::faisceauIsActive()
{
    return faisceauActive;
}

void faisceau_model::setFaisceauInactive()
{
    faisceauActive = false;
}

faisceau_model::faisceau_model(pile_model *pile , QPoint tl, QPoint br){
    topLeft = tl;
    botRight = br;

    faisceauActive = false;

    p_Piles = pile;
}

