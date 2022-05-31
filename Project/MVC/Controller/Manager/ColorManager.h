#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <QObject>

class ColorManager : public QObject
{
    Q_OBJECT
public:
    static ColorManager& Instance();

public:
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
    explicit ColorManager(QObject *parent = nullptr);
    ColorManager(const ColorManager&) = delete;
    ColorManager& operator=(const ColorManager&) = delete;

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

#endif // COLORMANAGER_H
