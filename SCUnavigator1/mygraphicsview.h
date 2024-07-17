#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include<QtWidgets>

class MyGraphicsView:public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr):QGraphicsView(parent)
    {
        maxScale=1.5;
        minScale=0.3;
    }
    MyGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr):QGraphicsView(scene,parent)
    {
        maxScale=1.5;
        minScale=0.3;
    }
    void wheelEvent(QWheelEvent *event);

    qreal currentScale;//当前缩放大小;

    qreal maxScale; // 最大缩放因素;
    qreal minScale;

};

#endif // MYGRAPHICSVIEW_H
