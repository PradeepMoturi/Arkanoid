#include "pause_menu.h"
#include "ui_pause_menu.h"
#include "game.h"
#include <QDebug>
extern Game* game;

pause_menu::pause_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pause_menu)
{
    setFixedSize(350, 350);
    ui->setupUi(this);
}

pause_menu::~pause_menu()
{
    delete ui;
}

void pause_menu::on_exit_clicked()
{
    qApp->exit();
}

void pause_menu::on_resume_clicked()
{
    game->start();
    this->deleteLater();
}

void pause_menu::on_replay_clicked()
{
    game->restart();
    this->deleteLater();
}
