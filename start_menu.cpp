#include "ui_start_menu.h"
#include "start_menu.h"
#include <QApplication>
#include "game.h"

extern Game* game;

start_menu::start_menu(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::start_menu)
{
    ui->setupUi(this);
}

start_menu::~start_menu()
{
    delete ui;
}


void start_menu::on_play_clicked()
{
    QString name = ui->nameEdit->text();
    game->start();
}


void start_menu::on_exit_clicked()
{
    qApp->exit();
}
