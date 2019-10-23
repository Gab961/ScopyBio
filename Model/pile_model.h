#ifndef PILE_MODEL_H
#define PILE_MODEL_H

#include <vector>
#include <iostream>
#include <fstream>

#include "image_model.h"

using namespace std;

class pile_model
{
private:
    vector<image_model> images;
    image_model* currentImages;

public:
    pile_model();
    void load(string path);
    void save(string path);
};

#endif // PILE_MODEL_H
