#include "pausemenu.h"
#include <QVBoxLayout>
#include "game.h"
#include <QLabel>
#include <QApplication>
extern Game *game;
PauseMenu::PauseMenu(QWidget *parent): QMainWindow(parent)
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

    // Add Score to layout
    QLabel *label_score = new QLabel(this);
    label_score->setText(QString("Score : ") + QString::number(game->score->getscore()));
    label_score->setStyleSheet("font: 40px; color: yellow");
    label_score->setAlignment(Qt::AlignCenter);
    label_score->setGeometry(QRect(QPoint(50, 80), QSize(600, 100)));
    label_score->show();


    // Create the required buttons
    m_resume = new CustomButton("Resume");
    m_restart = new CustomButton("Restart");
    m_exitGame = new CustomButton("Exit");

    // Set the layout of the central widget
    wid->setLayout(layout);

    // Add buttons to layout
    layout->addWidget(m_resume);
    layout->addWidget(m_restart);
    layout->addWidget(m_exitGame);

    // Set alignment and spacing of layout
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(50);

    // Set size of buttons
    m_resume->setFixedSize(QSize(200,50));
    m_restart->setFixedSize(QSize(200,50));
    m_exitGame->setFixedSize(QSize(200,50));


    // Connect the buttons to the appropriate slots
    connect(m_resume,SIGNAL(pressed()),m_resume,SLOT(changeColor()));
    connect(m_restart,SIGNAL(pressed()),m_restart,SLOT(changeColor()));
    connect(m_exitGame,SIGNAL(pressed()),m_exitGame,SLOT(changeColor()));
    connect(m_resume, SIGNAL(released()), this, SLOT(handleResume()));
    connect(m_restart, SIGNAL(released()), this, SLOT(handleRestart()));
    connect(m_exitGame, SIGNAL(released()), this, SLOT(handleEndGame()));
}


void PauseMenu::handleResume()
{
    game->start();
    this->deleteLater();
}

void PauseMenu::handleRestart()
{
    game->restart();
    this->deleteLater();
}

void PauseMenu::handleEndGame()
{
    this->close();
    qApp->exit();
}
