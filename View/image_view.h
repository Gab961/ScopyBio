#pragma once
#include <string>
#include <chrono>

#include <QGridLayout>
#include <QLabel>
#include <QPoint>
#include <QGroupBox>

using namespace std::chrono;

class ScopyBio_Controller;

class Image_View : public QGroupBox
{
    Q_OBJECT

public:
    /**
     * @brief Image_View
     * @param parent
     * @param scopybioController
     */
    Image_View( QWidget* parent, ScopyBio_Controller *scopybioController);

    /**
     * @brief createView : Create the empty view
     */
    void createView();

    /**
     * @brief connections
     */
    void connections();

    /**
     * @brief updateZoomOnly
     */
    void updateZoomOnly();

    /**
     * @brief mousePressEvent : Get the position of the first point clicked and if the pen or
     *                          the eraser tool is activated, set firstPenDraw to true
     * @param ev
     */
    void mousePressEvent(QMouseEvent* ev);

    /**
     * @brief mouseReleaseEvent :  - Short click : Ask to show a point
     *                             - Long click : Ask to show a rectangle between the first point and the last one
     * @param ev
     */
    void mouseReleaseEvent(QMouseEvent* ev);

    /**
     * @brief mouseMoveEvent : If the pen or the eraser tool is activated and firstPenDraw = true,
     *                         get the position of the first point clicked
     *                         else, draw a ligne between the first position and the new one.
     * @param ev
     */
    void mouseMoveEvent(QMouseEvent* ev);

signals:
    void drawCircleOnMouse( const QPoint& );
    void drawRectOnMouse(const QPoint&, const QPoint&, int labelWidth, int labelHeight);
    void changeZoomedPicture(int zoneWidth, int zoneHeight);
    void processResults(int labelWidth, int labelHeight);
    void pipetteClicked();
    void getDataFromArea(const QPoint&, int labelWidth, int labelHeight);
    void changeZoomPicture();
    void changeGraphPicture();
    void userAnalyseReady();
    void activateLocalAnalyse();
    void desactivateLocalAnalyse();
    void clearDataView();
    void askTextContent();

public slots:
    /**
     * @brief setNewPicture : Replace the picture in the label by the one in the path
     */
    void setNewPicture();

    /**
     * @brief readyForPipetteClick
     */
    void readyForPipetteClick();

    /**
     * @brief readyForPenDraw
     */
    void readyForPenDraw();

    /**
     * @brief cancelPenDraw
     */
    void cancelPenDraw();

    /**
     * @brief askProcessFromZoom : Ask to launch analysis if the white value was given
     */
    void askProcessFromZoom();

    /**
     * @brief nouvelleSelectionUtilisateur : Draw rectangle on the picture and create the zoom view associated
     * @param pos1 First point clicked
     * @param pos2 Point where the mouse is released
     * @param labelWidth
     * @param labelHeight
     */
    void nouvelleSelectionUtilisateur(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    /**
     * @brief startUserAnalysis
     */
    void startUserAnalysis();

    /**
     * @brief getData : Get the datas of the area clicked and send signals to refresh views
     * @param area : Point clicked
     * @param labelWidth
     * @param labelHeight
     */
    void getData(QPoint area, int labelWidth, int labelHeight);

    /**
     * @brief receiveTextContent : Get the text to write from menu_option
     * @param content
     */
    void receiveTextContent(QString content);

private:
    QString textContent;
    QPoint origPoint;
    QPoint secondPoint;
    quint64 TEMPS_CLIC_LONG;
    quint64 TEMPS_CLIC_DESSIN;
    quint64 temps_pression_orig;

    bool listenPipetteClick;
    bool listenPenClick = false;
    bool firstPenDraw = true;

    ScopyBio_Controller *m_scopybioController;
    QGridLayout *m_layout;
    QLabel *m_image;

    int m_zoneWidth;
    int m_zoneHeight;
};
