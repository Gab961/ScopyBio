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
        LayerView(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();
        void hoverEnter(QHoverEvent * event);
        void hoverLeave(QHoverEvent * event);
        void hoverMove(QHoverEvent * event);
        bool event(QEvent * e);
        void rowChanged(int row);
        void hoverRowChanged(int row);

    signals:
        void actionDoneWithLayer();

    public slots:
        void loadLayers(int currentRow);
        void removeLayer();
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
