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
