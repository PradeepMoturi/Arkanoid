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

private slots:
    void on_exit_clicked();
    void on_resume_clicked();
    void on_replay_clicked();

signals:
    void start();

private:
    Ui::pause_menu *ui;
};

#endif // PAUSE_MENU_H
