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
public:
    load_model();

    /**
     * @brief loadCalques return all the layers
     * @param path path of the project file
     * @return list of layers (calque class), empty if null.
     */
    std::vector<calque> loadCalques(std::string path);

    /**
     * @brief loadResults return the result of analysis
     * @param path path of the project file
     * @return list of results (Resultat class), empty if null
     */
    std::vector<Resultat> loadResults(std::string path);

    /**
     * @brief loadColRowAmounts return the number of row and column used for the results
     * @param path path of the project file
     * @return vector of int, the first int for row and the second for column. Empty if null
     */
    std::vector<int> loadColRowAmounts(std::string path);

    /**
     * @brief loadResultCalque return the layer of the result
     * @param path path of the project file
     * @return the path of where the layer is stored, empty if null
     */
    std::string loadResultCalque(std::string path);

    /**
     * @brief loadWhiteValue return the white value used to analysis
     * @param path path of the project file
     * @return the white value, -1 if null
     */
    int loadWhiteValue(std::string path);
};
