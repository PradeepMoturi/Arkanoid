#include "ui_start_menu.h"
#include "start_menu.h"
#include <QApplication>
#include "game.h"
#include <QDebug>
#include <QPixmap>

extern Game* game;
extern QString name;
start_menu::start_menu(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::start_menu)
{
    setFixedSize(700, 700);
    ui->setupUi(this);
    ui->mode->addItem("Power up");
    ui->lcdNumber->display(10);
}

start_menu::~start_menu()
{
    delete ui;
}

void start_menu::on_play_clicked()
{
    QString name = ui->nameEdit->text();
    game->build();
    this->deleteLater();
}

void start_menu::on_exit_clicked()
{
    qApp->exit();
}
