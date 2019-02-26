#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem (parent)
{
    // Initialise Score to Zero
    score = 0;

    // Displaying Score text on the Screen
    setPlainText(QString("Score : ") + QString::number(score));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 30));
}

void Score::increase()
{
    score++;
    setPlainText(QString("Score : ") + QString::number(score));
}

int Score::getscore()
{
    return score;
}
