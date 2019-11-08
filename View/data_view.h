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
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    void createView();

    void mousePressEvent( QMouseEvent* ev );
    void hoverEnter(QHoverEvent * event);
    void hoverLeave(QHoverEvent * event);
    void hoverMove(QHoverEvent * event);
    bool event(QEvent * e);

signals:
    void graphClic(int itemIndex);

public slots:
    void processingResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

private:
    void drawResults();
    bool mouseInLabel(QPoint pos);

    ScopyBio_Controller *m_scopybioController;
    QGridLayout *m_layout;
    QLabel *m_image;
};
