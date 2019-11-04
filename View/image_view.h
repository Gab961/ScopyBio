#pragma once
#include <QLabel>
#include <string>
#include <chrono>
using namespace std::chrono;

class Image_View : public QLabel
{
    Q_OBJECT


public:
    Image_View( QWidget* parent = 0);

    void mousePressEvent( QMouseEvent* ev );
    void mouseReleaseEvent( QMouseEvent* ev);

signals:
    void drawCircleOnMouse( const QPoint& );
    void drawRectOnMouse(const QPoint&, const QPoint&);


public slots:
    void setNewPicture(std::string path);



private:
    QPoint origPoint;
    quint64 TEMPS_CLIC_LONG;
    quint64 temps_pression_orig;
};
