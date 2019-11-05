#pragma once
#include <QLabel>
#include <QGridLayout>

class Zoom_View : public QLabel
{
    Q_OBJECT

    public slots:
        void setNewPicture(std::string path);

    public:
        Zoom_View(QWidget* parent = 0);

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
};
