#pragma once

#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <iostream>

class ScopyBio_Controller;

class LayerView: public QListWidget
{
    Q_OBJECT

    public:
        LayerView(QWidget *parent, ScopyBio_Controller *scopybioController);
        // TODO
        void createView();
        void connections();

    signals:
//        void contextMenuRequest(const QPoint&);

    public slots:
        void loadLayers(int currentRow);
//        void showContextMenu(const QPoint&);
//        void eraseLayer();
//        void newLayer();
//        void showLayer();
//        void hideLayer();

    private:
        QWidget *m_line;
        QGridLayout *m_itemLayout;
        QPushButton *m_delete;
        QPushButton *m_hide;
        QLabel *m_layerId;
        ScopyBio_Controller *m_scopybioController;
};
