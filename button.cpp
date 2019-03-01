#include "button.h"

CustomButton::CustomButton(const QString textValue)
{
    this->setText(textValue);
}

void CustomButton::changeColor()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QPalette p = pButton->palette();
    p.setColor(QPalette::Button, Qt::yellow);
    pButton->setPalette(p);
}
