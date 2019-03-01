#include "startpage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include "game.h"

extern Game* game;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // Add title
    QLabel* mainTitle = new QLabel("ARKANOID", this);
    QFont f("Arial", 32, QFont::Bold);
    mainTitle->setStyleSheet("QLabel {color : white;}");
    mainTitle->setFont(f);
    mainTitle->setGeometry(235, 50, 350, 50);

    QLabel *instructions = new QLabel(this);
    instructions->setText("<u>INSTRUCTIONS:</u>"
                          "<br><br>Use Arrow Keys to Move the paddle<br><br>"
                          "Press Esc key to pause the game");
    instructions->setStyleSheet("font: 20px; color: yellow");
    instructions->setAlignment(Qt::AlignCenter);
    instructions->setGeometry(QRect(QPoint(60, 80), QSize(600, 180)));
    instructions->show();

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
    m_new_game = new CustomButton("New Game");
    m_exitGame = new CustomButton("Exit");


    // Set the layout of the central widget
    wid->setLayout(layout);

    // Add buttons to layout
    //layout->addWidget(m_instructions);
    layout->addWidget(m_new_game);
    layout->addWidget(m_exitGame);

    // Set alignment and spacing of layout
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);

    // Set size of buttons
    //m_instructions->setFixedSize(QSize(200,50));
    m_new_game->setFixedSize(QSize(200,50));
    m_exitGame->setFixedSize(QSize(200,50));


    // Connect the buttons to the appropriate slots
    connect(m_new_game,SIGNAL(pressed()),m_new_game,SLOT(changeColor()));
    connect(m_exitGame,SIGNAL(pressed()),m_exitGame,SLOT(changeColor()));
    connect(m_new_game, SIGNAL(released()), this, SLOT(handleNewGame()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleExitGame()));
}

void MainWindow::handleNewGame()
{
    game->build();
    delete this;
}

void MainWindow::handleExitGame()
{
    this->close();

}
