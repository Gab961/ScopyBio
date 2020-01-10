#pragma once

#include <QListWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QGridLayout>
#include <iostream>
#include <QHoverEvent>

class ScopyBio_Controller;

class LayerView: public QListWidget
{
    Q_OBJECT

    public:
        /**
         * @brief LayerView
         * @param parent
         * @param scopybioController
         */
        LayerView(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief mousePressEvent : Select the layer at the mouse position
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
         * @brief hoverMove : Detect the layer at the mouse position
         * @param event
         */
        void hoverMove(QHoverEvent * event);

        /**
         * @brief event : Mouse movments on the view
         * @param e
         * @return
         */
        bool event(QEvent * e);

        /**
         * @brief rowChanged : Set the current layer row
         * @param row
         */
        void rowChanged(int row);

        /**
         * @brief hoverRowChanged : Set the current hover layer row
         * @param row
         */
        void hoverRowChanged(int row);

    signals:
        void actionDoneWithLayer();

    public slots:
        /**
         * @brief loadLayers : Create the view
         * @param currentRow
         */
        void loadLayers(int currentRow);

        /**
         * @brief removeLayer : Remove the layer when the corresponding delete button is pressed
         */
        void removeLayer();

        /**
         * @brief hideLayer : Hide or show the layer when the corresponding hide button is pressed
         */
        void hideLayer();

    private:
        int currentLayerRow;
        int currentLayerRowHover;

        QWidget *m_line;
        QGridLayout *m_itemLayout;
        QPushButton *m_delete;
        QPushButton *m_hide;
        QLabel *m_layerId;
        std::vector<int> layerIdList;
        ScopyBio_Controller *m_scopybioController;
};
