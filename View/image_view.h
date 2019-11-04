#pragma once
#include <QLabel>
#include <QPoint>
#include <string>
#include <chrono>
using namespace std::chrono;

class Image_View : public QLabel
{
    Q_OBJECT

public:
    Image_View( QWidget* parent = 0);
    void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);

    void mousePressEvent( QMouseEvent* ev );
    void mouseReleaseEvent( QMouseEvent* ev);

signals:
    void drawCircleOnMouse( const QPoint& );
    void drawRectOnMouse(const QPoint&, const QPoint&);
    void changeZoomedPicture(std::string path);

public slots:
    void setNewPicture(std::string path);

private:
    std::string path;
    QPoint origPoint;
    quint64 TEMPS_CLIC_LONG;
    quint64 temps_pression_orig;

    //TODO Voir si on les garde
    std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
};
