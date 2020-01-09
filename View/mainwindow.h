#pragma once

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QPushButton>
#include <QGroupBox>

class LayerView;
class Pile_View;
class menu_option;
class Image_View;
class Zoom_View;
class Menu_Draw_Button;
class Data_View;
class ScopyBio_Controller;
class LoopView;
class ComparePopup;
class AnalysisPopup;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief createView : Assemble the different widgets to create the main view
     */
    void createView();

    /**
     * @brief connections
     */
    void connections();

    /**
     * @brief wheelEvent : Change the picture shown
     * @param ev
     */
    void wheelEvent(QWheelEvent *ev);

    /**
     * @brief changeStateGrid : Hide or show the grid on zoom view
     */
    void changeStateGrid();

signals:
    void sendPath(std::string path);
    void sendPathProjet(std::string path);
    void changeMainPicture();
    void changeZoomedPicture();
    void clearZoomView();
    void clearDataView();
    void initAtFirstItemInPile(int i);

public slots:
    /**
     * @brief open : Open the selected file (.tiff) and manage the buttons depending
     *               of the format (16 or 24 bits)
     */
    void open();

    /**
     * @brief save : Save the project
     */
    void save();

    /**
     * @brief undo : Cancel the previous actions and rebuild the view
     */
    void undo();

    /**
     * @brief redo : Recreate the cancelled actions and rebuild the view
     */
    void redo();

    /**
     * @brief saveAs : Save the project in a specific location
     */
    void saveAs();

    /**
     * @brief saveCurrentDisplay : Save only the current picture with its layers
     */
    void saveCurrentDisplay();

    /**
     * @brief aboutUs : Informative popup about us
     */
    void aboutUs();

    /**
     * @brief howToUse : User manual
     * TODO
     */
    void howToUse();

    /**
     * @brief showFirstInPile : When the project is load, show the first picture of the pile
     *
     */
    void showFirstInPile();

    /**
     * @brief changeActualItem : Change the picture on the image view and the zoom view according
     *                           to the selected one
     */
    void changeActualItem();

    /**
     * @brief openProject : Open the project at the specified path
     * @param path
     */
    void openProject(std::string path);

    /**
     * @brief startFullAnalysis : Clear the zoom and the data view and launch the analysis
     *                            on the picture
     */
    void startFullAnalysis();

    /**
     * @brief userAnalysisEnded : Update the zoom view with the grid of the results of user analysis
     */
    void userAnalysisEnded();

    /**
     * @brief fullAnalysisEnded : Update the image view with the grid of the results of user analysis
     */
    void fullAnalysisEnded();

    /**
     * @brief recreateMainDisplay
     */
    void recreateMainDisplay();

protected:
    /**
     * @brief closeEvent : Remove the tmp directory when the app is closed
     * @param e
     */
    void closeEvent(QCloseEvent* e) override;

private:
    /**
     * @brief createActions : Create the action bar
     */
    void createActions();

    /**
     * @brief updateSaveAs : Enable save as
     */
    void updateSaveAs();

    /**
     * @brief updateSave : Enable save
     */
    void updateSave();

    /**
     * @brief nouveauClicCreerRectangle
     * @param pos1
     * @param pos2
     */
    void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);

    /**
     * @brief resizeEvent : Update the view when the window is resized to keep the proportions
     * @param event
     */
    void resizeEvent(QResizeEvent* event);

    /**
     * @brief setCursorPipetteActive : Edit the cursor on each view when the pipette is enabled
     */
    void setCursorPipetteActive();

    /**
     * @brief setCursorPipetteDisabled : Edit the cursor on each view when the pipette is disabled
     */
    void setCursorPipetteDisabled();

    QGridLayout *m_leftLayout;
    Zoom_View *m_zoomView;
    Menu_Draw_Button *m_tools;
    menu_option *m_options;

    QGridLayout *m_centerLayout;
    QGridLayout *m_buttonLayout;
    Image_View *m_imageView;
    LoopView *m_loopWindow;
    ComparePopup *m_comparePopup;

    QGridLayout *m_rightLayout;
    QGridLayout *m_layerLayout;
    QGridLayout *m_pileLayerLayout;
    QGroupBox *m_layer;
    Data_View *m_dataView;
    Pile_View *m_pileView;
    LayerView *m_layerView;
    QPushButton *m_newLayer;

    QAction *m_loadFile;
    QAction *m_saveFile;
    QAction *m_saveAs;
    QAction *m_saveCurrentDisplay;
    QAction *m_aboutUs;
    QAction *m_howToUse;
    QAction *m_compare;
    QAction *m_loop;
    QAction *m_undo;
    QAction *m_redo;

    AnalysisPopup *m_analysisPopup;

    QWidget *m_window;
    QGridLayout *m_mainLayout;

    ScopyBio_Controller *m_scopybioController;
};

