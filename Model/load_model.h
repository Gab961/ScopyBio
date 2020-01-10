#pragma once

#include <string>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <vector>

class calque;
class Resultat;
class Qpoint;

//TODO Fonction pour lire le fichier qu'une seule fois au lieu qu'à chaque fonction ?
class load_model
{
private:
    Json::Value sauvegarde;
public:
    load_model();

    /**
     * @brief loadJsonValue open the file project and save the json in a variable
     * @param path path of the project file
     */
    void loadJsonValue(std::string path);

    /**
     * @brief loadCalques return all the layers
     * @return list of layers (calque class), empty if null.
     */
    std::vector<calque> loadCalques();

    /**
     * @brief loadResults return the result of analysis
     * @return list of results (Resultat class), empty if null
     */
    std::vector<Resultat> loadResults();

    /**
     * @brief loadColRowAmounts return the number of row and column used for the results
     * @return vector of int, the first int for row and the second for column. Empty if null
     */
    std::vector<int> loadColRowAmounts();

    /**
     * @brief loadResultCalque return the layer of the result
     * @return the path of where the layer is stored, empty if null
     */
    std::string loadResultCalque();

    /**
     * @brief loadWhiteValue return the white value used to analysis
     * @return the white value, -1 if null
     */
    int loadWhiteValue();
};
