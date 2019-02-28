#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class CustomButton: public QPushButton
{
Q_OBJECT

public:
    CustomButton();
    CustomButton(const QString textValue);
    CustomButton(const QString textValue, QWidget* paren);
    CustomButton(QWidget* paren);

public slots:
    void changeColor();
};

#endif // BUTTON_H
