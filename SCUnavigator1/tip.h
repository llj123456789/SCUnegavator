#ifndef TIP_H
#define TIP_H

#include <QDialog>

namespace Ui {
class screen;
}

class tip : public QDialog
{
    Q_OBJECT

public:
    explicit tip(QWidget *parent = nullptr);
    ~tip();

public:
    Ui::screen *ui;
private slots:
    void on_pushButton_clicked();
};

#endif // TIP_H
