#pragma once

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

class Menu_Draw_Button: public QGroupBox
{
    Q_OBJECT

    public:
        Menu_Draw_Button(QWidget *parent);

    private:
        QGridLayout *m_gridTools;

        QPushButton *m_eraser;
        QPushButton *m_removeSelectedZone;
        QPushButton *m_pen;
        QPushButton *m_selectSquare;
        QPushButton *m_selectCircle;
        QPushButton *m_selectDraw;
};
