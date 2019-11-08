#ifndef FAISCEAU_MODEL_H
#define FAISCEAU_MODEL_H

#include <coordonnee.h>
#include <data_model.h>
#include <pile_model.h>
#include <vector>

class faisceau_model
{
private:
    coordonnee topLeft;
    coordonnee botRight;

    data_model Data;
    pile_model *p_Piles;

public:
    faisceau_model();
    faisceau_model(pile_model *pile,coordonnee tl,coordonnee br);

    coordonnee getTopLeft() const;
    void setTopLeft(const coordonnee &value);

    coordonnee getBotRight() const;
    void setBotRight(const coordonnee &value);

    data_model getData() const;
    void setData(const data_model &value);

    pile_model *getP_Piles() const;
    void setP_Piles(pile_model *value);

    void fillData();
};

#endif // FAISCEAU_MODEL_H
