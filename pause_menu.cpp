/*
Copyright (c) 2019 Revanth Babu, Pradeep Moturi, Jeevan Chandra, Udit Maniyar

This file is part of Arkanoid 
(see https://github.com/IITH-SBJoshi/concurrency-1).

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
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
    ui->lcdNumber_2->display(game->score->getscore());
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
    delete this;
}

void pause_menu::on_replay_clicked()
{
    game->restart();
    this->deleteLater();
}

