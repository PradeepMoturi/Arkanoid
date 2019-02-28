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
    ui->curr_score->display(game->score->getscore());
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

