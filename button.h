#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

/*!
 * \brief The CustomButton class
 *
 * This class is used to create Pushbutton.
 */
class CustomButton: public QPushButton
{
Q_OBJECT

public:
    /*!
     * \brief CustomButton
     * \param textValue
     *
     * It is the constructor of the CustomButton class.
     * It takes String as an argument and create a PushButton for the argument.
     */
    CustomButton(const QString textValue);

public slots:
    /*!
     * \brief changeColor
     *
     * It changes the colour of the button to yellow when pressed.
     */
    void changeColor();
};

#endif // BUTTON_H
