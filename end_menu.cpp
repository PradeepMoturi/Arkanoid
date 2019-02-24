#include "end_menu.h"
#include "ui_end_menu.h"

end_menu::end_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end_menu)
{
    ui->setupUi(this);
}

end_menu::~end_menu()
{
    delete ui;
}
