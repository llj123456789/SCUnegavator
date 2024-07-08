#include "mygraphicsview.h"


void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    qreal delta = event->angleDelta().y();

    currentScale = transform().m11();


    if(delta>0&&currentScale<maxScale)
    {
        scale(1.1,1.1);
    }
    else if(delta<0 && currentScale>minScale)
    {
        scale(0.9,0.9);
    }



}
