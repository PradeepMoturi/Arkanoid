#ifndef START_MENUI_H
#define START_MENUI_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>

namespace Ui {
class start_menu;
}

class start_menu : public QGraphicsView
{
    Q_OBJECT

public:
    explicit start_menu(QWidget *parent = nullptr);
    QGraphicsScene *scene;
    QPushButton *play;
    QPushButton *exit;
    ~start_menu();

private slots:

    void on_play_clicked();

    void on_exit_clicked();

private:
    Ui::start_menu *ui;
};

#endif // START_MENUI_H
