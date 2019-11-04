#pragma once
#include <QLabel>

class Zoom_View : public QLabel
{
    Q_OBJECT

public slots:
    void setNewPicture(std::string path);

public:
    Zoom_View(QWidget* parent = 0);
};
