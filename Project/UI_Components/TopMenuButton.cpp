#include "TopMenuButton.h"

TopMenuButton::TopMenuButton(QWidget *parent)
    : QWidget{parent}
    , _mainColor(Settings::GetInstance()._top_panel_menubutton_idle_color)
    , _buttonText("Button")
    , _isPressed(false)
{
    setFixedWidth(3 * 6 + 40);
}

void TopMenuButton::SetText(QString value)
{
    this->_buttonText = value;
    setFixedWidth(this->_buttonText.size() / 2 * 6 + 40);
}

void TopMenuButton::enterEvent(QEnterEvent *event)
{
    (void)event;

    this->_mainColor = Settings::GetInstance()._top_panel_menubutton_enter_color;
    update();
}

void TopMenuButton::leaveEvent(QEvent *event)
{
    (void)event;

    this->_mainColor = Settings::GetInstance()._top_panel_menubutton_idle_color;
    update();
}

void TopMenuButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainColor = Settings::GetInstance()._top_panel_menubutton_press_color;
        this->_isPressed = true;
        update();
    }
}

void TopMenuButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->_mainColor = Settings::GetInstance()._top_panel_menubutton_enter_color;
        this->_isPressed = false;
        update();
        emit this->clicked();
    }
}

void TopMenuButton::paintEvent(QPaintEvent *event)
{
    (void)event;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(this->_mainColor), 0.1));
    painter.setBrush(QColor(this->_mainColor));

    // draw background rectangle
    painter.drawRoundedRect(QRectF(0,
                                   !this->_isPressed ? 0 : 1,
                                   width(),
                                   height() - 1),
                            4, 4);

    // draw text
    painter.setPen(QPen(QColor(Settings::GetInstance()._top_panel_menubutton_text_color), 1));
    painter.drawText(width() / 2 - this->_buttonText.size() / 2 * 6, height() / 2 + 4 + (!this->_isPressed ? 0 : 1), this->_buttonText);
}
