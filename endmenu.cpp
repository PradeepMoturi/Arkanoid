#include "endmenu.h"
#include "startpage.h"
#include "game.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>

extern Game *game;

EndMenu::EndMenu(QWidget *parent): QMainWindow(parent)
{
    // Add Score


    // Widget to add buttons
    QWidget* wid = new QWidget(this);

    QPalette palette;
    palette.setBrush(QPalette::Button,Qt::gray);
    palette.setBrush(QPalette::Background, QBrush(QImage(":/Images/data/Images/Main_Menu_BG.jpg").scaled(700,700)));
    this->setPalette(palette);

    // Resize and show MainWindow
    this->resize(700, 700);
    this->setFixedSize(700,700);
    this->move(0, 0);

    // Set wid as the central widget of MainWindow
    this->setCentralWidget(wid);

    // Create a vertical layout for buttons
    QVBoxLayout* layout = new QVBoxLayout();



    // Create the required buttons
    //m_instructions = new CustomButton("Instructions");
    m_restart = new CustomButton("Restart");
    m_exitGame = new CustomButton("Exit");


    // Set the layout of the central widget
    wid->setLayout(layout);

    // Add buttons to layout
    //layout->addWidget(m_instructions);
    layout->addWidget(m_restart);
    layout->addWidget(m_exitGame);

    // Set alignment and spacing of layout
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);

    // Set size of buttons
    //m_instructions->setFixedSize(QSize(200,50));
    m_restart->setFixedSize(QSize(200,50));
    m_exitGame->setFixedSize(QSize(200,50));


    // Connect the buttons to the appropriate slots
    connect(m_restart,SIGNAL(pressed()),m_restart,SLOT(changeColor()));
    connect(m_exitGame,SIGNAL(pressed()),m_exitGame,SLOT(changeColor()));
    connect(m_restart, SIGNAL(released()), this, SLOT(handleRestart()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleEndGame()));
}

void EndMenu::handleRestart()
{
    game->restart();
    this->deleteLater();
}

void EndMenu::handleEndGame()
{
    this->close();
}

