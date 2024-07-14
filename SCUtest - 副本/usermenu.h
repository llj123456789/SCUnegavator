#ifndef USERMENU_H
#define USERMENU_H

#include <QDialog>

namespace Ui {
class userMenu;
}

class userMenu : public QDialog
{
    Q_OBJECT

public:
    explicit userMenu(QWidget *parent = nullptr);
    ~userMenu();

private:
    Ui::userMenu *ui;
};

#endif // USERMENU_H
