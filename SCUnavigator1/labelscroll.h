#ifndef LABELSCROLL_H
#define LABELSCROLL_H

#include <QLabel>
#include<QDebug>
#include<QTimerEvent>
#include<QPaintEvent>
#include<QTextDocument>
#include<QPainter>

class LabelScroll : public QLabel
{
    Q_OBJECT
public:
    LabelScroll(QWidget *parent = nullptr);
    ~LabelScroll();

    void updateLabelRollingState();
public slots:
    void timerEvent(QTimerEvent* e) Q_DECL_OVERRIDE;

    void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;

    void setText(const QString &txt);

    //设置图片，主要把lt设回0，使其恢复正常的图片显示
    void setPixmap(const QPixmap &pix);

    //窗口变化事件
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

    // 根据给定的数值，修改滚动速度 sp是一次滚动多少像素,st是多少秒触发一次滚动
    void setspeed(int sp=5,int st=300);

private:
    int timerId; //定时器id
    int text_wpixel; //储存的当前label内字符串的像素水平长度

    int speedt;// 多久触发一次滚动
    int spixel;// 一次滚动多少像素

    int left;// 标明当前的像素滚动量

    QString blank;//空格
    int blank_wp;//空格的像素宽度

    int start_scroll;

    uint8_t flag; //判断是否应该开启滚动 0否 1真

};

#endif // LABELSCROLL_H
