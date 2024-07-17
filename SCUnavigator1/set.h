#ifndef SET_H
#define SET_H

#include <QDialog>
#include"negvator.h"

namespace Ui {
class Set;
}

class Set : public QDialog
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = nullptr);
    negvator* neg;
    ~Set();

private slots:
    void on_comboBox_2_activated(int index);

    void on_roadColor_activated(int index);

    void on_pushButton_3_clicked();

private:
    Ui::Set *ui;
};

#endif // SET_H
