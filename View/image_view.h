#pragma once
#include <QLabel>
#include <QPoint>
#include <string>
#include <chrono>
using namespace std::chrono;

class ScopyBio_Controller;

class Image_View : public QLabel
{
    Q_OBJECT

public:
    Image_View( QWidget* parent, ScopyBio_Controller *scopybioController);
    void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);

    void mousePressEvent( QMouseEvent* ev );
    void mouseReleaseEvent( QMouseEvent* ev);

signals:
    void drawCircleOnMouse( const QPoint& );
    void drawRectOnMouse(const QPoint&, const QPoint&);
    void changeZoomedPicture();
    void processResults(QPoint pos1, QPoint pos2);

public slots:
    void setNewPicture();

private:
    QPoint origPoint;
    quint64 TEMPS_CLIC_LONG;
    quint64 temps_pression_orig;

    ScopyBio_Controller *m_scopybioController;
};
