#ifndef END_MENU_H
#define END_MENU_H

#include <QWidget>

namespace Ui {
class end_menu;
}

class end_menu : public QWidget
{
    Q_OBJECT

public:
    explicit end_menu(QWidget *parent = nullptr);
    ~end_menu();

private slots:
    void on_exit_clicked();

    void on_replay_clicked();

private:
    Ui::end_menu *ui;
};

#endif // END_MENU_H