#pragma once
#include <QLabel>
#include <QDebug>
#include <QToolTip>
#include <QGroupBox>
#include <QGridLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QHoverEvent>
#include <vector>

class ScopyBio_Controller;

class Data_View : public QGroupBox
{
    Q_OBJECT

    public:
        /**
         * @brief Data_View
         * @param parent
         * @param scopybioController
         */
        Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView : Create the empty view
         */
        void createView();

        /**
         * @brief mousePressEvent : Get the point clicked on the graph and ask to show
         *                          the corresponding picture
         * @param ev
         */
        void mousePressEvent(QMouseEvent* ev);

        /**
         * @brief hoverEnter
         * @param event
         */
        void hoverEnter(QHoverEvent * event);

        /**
         * @brief hoverLeave
         * @param event
         */
        void hoverLeave(QHoverEvent * event);

        /**
         * @brief hoverMove : Show in tooltip widget the picture corresponding to the hovered over area
         * @param event
         */
        void hoverMove(QHoverEvent * event);

        /**
         * @brief event : Mouse movments on the view
         * @param e
         * @return
         */
        bool event(QEvent * e);

    signals:
        void graphClic(int itemIndex);

    public slots:
        /**
         * @brief processingResults : Launch analysis and call drawResults()
         * @param labelWidth
         * @param labelHeight
         */
        void processingResults(int labelWidth, int labelHeight);

        /**
         * @brief setGraphFromFile : Put the saved graph area in the view.
         */
        void setGraphFromFile();

        /**
         * @brief enableDisplay
         */
        void enableDisplay();

        /**
         * @brief resetDataView : Remove the graph area from the view.
         */
        void resetDataView();

    private:
        /**
         * @brief drawResults : TODO
         */
        void drawResults();

        /**
         * @brief mouseInLabel : Check if the current position is in the label
         * @param pos : Current position
         * @return
         */
        bool mouseInLabel(QPoint pos);

        ScopyBio_Controller *m_scopybioController;
        QGridLayout *m_layout;
        QLabel *m_image;
        bool readyToShow;
};
