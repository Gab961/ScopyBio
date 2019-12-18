#pragma once

#include <string>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <vector>

class calque;

class load_model
{
public:
    load_model();

    std::vector<calque> loadCalques(std::string path);
};
