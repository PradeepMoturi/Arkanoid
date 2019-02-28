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
