#ifndef COLORCONTROLLER_H
#define COLORCONTROLLER_H

#include <QString>

class ColorController final
{
private:
    ColorController();
    ~ColorController();
    ColorController(const ColorController&) = delete;
    ColorController& operator=(const ColorController&) = delete;

public:
    static ColorController &Instance();

    struct ButtonColors
    {
        QString idle;
        QString enter;
        QString press;
        QString color;
    };

    const ButtonColors& GetComputerButtonColors();
    const ButtonColors& GetTaskButtonColors();
    const ButtonColors& GetTaskButtonCloseButtonColors();

    const QString& GetLeftPanelColor();
    const QString& GetCenterPanelColor();
    const QString& GetRightPanelColor();
    const QString& GetTopPanelColor();
    const QString& GetCenterPanelBottomColor();

private:
    ButtonColors ComputerButtonColor;
    ButtonColors TaskButtonColor;
    ButtonColors TaskButtonCloseButtonColor;

    QString LeftPanelColor;
    QString CenterPanelColor;
    QString RightPanelColor;
    QString TopPanelColor;
    QString CenterPanelBottomColor;
};

#endif // COLORCONTROLLER_H
