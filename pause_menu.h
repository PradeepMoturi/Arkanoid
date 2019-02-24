#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <QWidget>

namespace Ui {
class pause_menu;
}

class pause_menu : public QWidget
{
    Q_OBJECT

public:
    explicit pause_menu(QWidget *parent = nullptr);
    ~pause_menu();

private:
    Ui::pause_menu *ui;
};

#endif // PAUSE_MENU_H
