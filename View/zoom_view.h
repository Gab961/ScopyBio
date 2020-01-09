#pragma once
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>

class ScopyBio_Controller;
class QMouseEvent;

class Zoom_View : public QGroupBox
{
    Q_OBJECT

    public:
        /**
         * @brief Zoom_View
         * @param parent
         * @param scopybioController
         */
        Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief mousePressEvent : If the pipette tool is activated, set a new white value,
         *                          else if an analysis was done, return the datas of the area
         *                          clicked.
         * @param ev
         */
        void mousePressEvent(QMouseEvent* ev);

        /**
         * @brief readyForClick : Wait for the next click which determine the new white value.
         */
        void readyForClick();

        /**
         * @brief createView : Create the empty view
         */
        void createView();

        /**
         * @brief getData : Get the datas of the area clicked.
         * @param area : Point clicked
         * @param labelWidth : Width of the label
         * @param labelHeight : Height of the label
         */
        void getData(QPoint area, int labelWidth, int labelHeight);

    public slots:
        /**
         * @brief setNewPicture : Put the new zoomed area in the view.
         * @param zoneWidth : Width of the zoomed area
         * @param zoneHeight : Height of the zoomed area
         */
        void setNewPicture(int zoneWidth, int zoneHeight);

        /**
         * @brief setPictureFromFile : Put the saved zoomed area in the view.
         */
        void setPictureFromFile();

        /**
         * @brief enableDisplay
         */
        void enableDisplay();

        /**
         * @brief resetZoomView : Remove the zoomed area from the view.
         */
        void resetZoomView();

    signals:
        void processResultsFromZoom();
        void pipetteClicked();
        void changeGraphPicture();

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
        QPushButton *m_hide;
        ScopyBio_Controller *m_scopybioController;
        bool readyToShow;
};
