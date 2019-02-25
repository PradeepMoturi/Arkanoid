#include "end_menu.h"
#include "ui_end_menu.h"
#include "game.h"

extern Game *game;

end_menu::end_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end_menu)
{
    setFixedSize(700, 700);
    ui->setupUi(this);
}

end_menu::~end_menu()
{
    delete ui;
}

void end_menu::on_exit_clicked()
{
    qApp->exit();
}

void end_menu::on_replay_clicked()
{
    game->restart();
    this->deleteLater();
}
