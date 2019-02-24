#include "pause_menu.h"
#include "ui_pause_menu.h"

pause_menu::pause_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pause_menu)
{
    ui->setupUi(this);
}

pause_menu::~pause_menu()
{
    delete ui;
}
