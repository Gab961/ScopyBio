#pragma once
#include "../definition.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
#include <string>

class calque;
class Resultat;
class Qpoint;

class save_model
{
public:
    save_model();

    /**
     * @brief saveTiff Save the pile (.tiff) in the save folder, in case of the original one is deleted
     */
    void saveTiff();

    /**
     * @brief saveInLocal copy the original pile (.tiff) temporarily to work in with.
     * @param sourcePath path of the original tiff file
     */
    void saveInLocal(std::string sourcePath);

    /**
     * @brief saveCalques save all layers in a folder "calques" in the save folder
     * @param calques the list of user layer to save
     * @param dataReady indicate if the res layer is ready or null
     * @param res the layer of the complete analysis
     */
    void saveCalques(std::vector<calque> calques, bool dataReady, calque res);

    /**
     * @brief saveJsonFile create a json file (with the .scb extension) where all main datas are stored
     * @param calques list of all user layers
     * @param resultats list of all results from complete analysis
     * @param row number of rows used for the analysis
     * @param col number of column used for the analysis
     * @param whiteValue white value used for the analysis
     */
    void saveJsonFile(std::vector<calque> calques, const std::vector<Resultat> &resultats, int row, int col, int whiteValue);

    /**
     * @brief save save automatically without asking the user where to save /!\ THE USER SHOULD SAVE_AS AT LEAST ONCE BEFORE USING IT
     * @param _calques the list of user layer to save
     * @param dataReady indicate if the res layer is ready or null
     * @param resultats list of all results from complete analysis
     * @param row number of rows used for the analysis
     * @param col number of column used for the analysis
     * @param res the layer of the complete analysis
     * @param whiteValue white value used for the analysis
     * @return false if it didn't save (because path of the folder isn't assigned), true if it did
     */
    bool save(std::vector<calque> _calques, bool dataReady, const std::vector<Resultat> & resultats, int row, int col, calque res, int whiteValue);

    //TODO Add feature : Convert the bmp image into pdf
    /**
     * @brief saveCurrentDisplay Save the current image with layer the user wants to store it
     * @param savePath the path of where the user wants to store it
     * @param currentDisplayPath the path of where the current image with layer is stored
     */
    void saveCurrentDisplay(std::string savePath, std::string currentDisplayPath);

    /**
     * @brief save_as save the work where the user wants. It Initializes path environments to know after where to store the project.
     * @param path the path of where the user want to save his work
     * @param fileName the path of the original tiff file
     * @param _calques the list of user layer to save
     * @param dataReady indicate if the res layer is ready or null
     * @param resultats list of all results from complete analysis
     * @param row number of rows used for the analysis
     * @param col number of column used for the analysis
     * @param res the layer of the complete analysis
     * @param whiteValue white value used for the analysis
     */
    void save_as(std::string path, std::string fileName, std::vector<calque> _calques, bool dataReady, std::vector<Resultat> resultats, int row, int col, calque res, int whiteValue);

    /**
     * @brief getFileName Get the name file from the path
     * @param filePath path of the file
     * @param withExtension true we want the extension, false else
     * @param seperator which separator is used for the path
     * @return the file name with or without the extension, empty if impossible
     */
    std::string getFileName(std::string filePath, bool withExtension, char seperator);

    /**
     * @brief changeSavePaths change the path of where the project should be stored /!\ ONLY USED BY LOAD_MODEL !
     * @param newSavePath
     */
    void changeSavePaths(std::string newSavePath);


private:
    std::string savePath;
    std::string saveCalquesPath;
    std::string filename;
    std::string localTiffSave;
};

