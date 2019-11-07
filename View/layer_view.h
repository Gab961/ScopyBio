#pragma once

#include <QListWidget>
#include <iostream>

class ScopyBio_Controller;

class LayerView: public QListWidget
{
    Q_OBJECT

    public:
        LayerView(QWidget *parent, ScopyBio_Controller *scopybioController);
        // TODO
        void createView();

    public slots:
        void loadLayers(std::string path);

    private:
        ScopyBio_Controller *m_scopybioController;
};
