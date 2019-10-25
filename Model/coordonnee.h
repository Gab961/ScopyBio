#ifndef COORDONNEE_H
#define COORDONNEE_H


class coordonnee
{
private:
    float x;
    float y;
public:
    coordonnee();
    coordonnee(float _x, float _y);

    float getY() const;
    void setY(float value);
    float getX() const;
    void setX(float value);
};

#endif // COORDONNEE_H
