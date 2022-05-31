#include "ColorManager.h"

ColorManager::ColorManager(QObject *parent)
    : QObject{parent}
{
    this->ComputerButtonColor.idle = "#36393F";
    this->ComputerButtonColor.enter = "#76B39D";
    this->ComputerButtonColor.press = "#589E85";

    this->TaskButtonColor.idle = "#2F3136";
    this->TaskButtonColor.enter = "#3C3F45";
    this->TaskButtonColor.press = "#3F4248";
    this->TaskButtonColor.color = "#96989D";

    this->TaskButtonCloseButtonColor.idle = "#2F3136";
    this->TaskButtonCloseButtonColor.enter = "#151617";
    this->TaskButtonCloseButtonColor.press = "#76B39D";

    this->LeftPanelColor = "#202225";
    this->CenterPanelColor = "#2F3136";
    this->RightPanelColor = "#36393F";
    this->TopPanelColor = "#36393F";
    this->CenterPanelBottomColor = "#292B2F";
}

ColorManager& ColorManager::Instance()
{
    static ColorManager instance;
    return instance;
}

const ColorManager::ButtonColors& ColorManager::GetComputerButtonColors()
{
    return this->ComputerButtonColor;
}

const ColorManager::ButtonColors& ColorManager::GetTaskButtonColors()
{
    return this->TaskButtonColor;
}

const ColorManager::ButtonColors& ColorManager::GetTaskButtonCloseButtonColors()
{
    return this->TaskButtonCloseButtonColor;
}

const QString& ColorManager::GetLeftPanelColor()
{
    return this->LeftPanelColor;
}

const QString& ColorManager::GetCenterPanelColor()
{
    return this->CenterPanelColor;
}

const QString& ColorManager::GetRightPanelColor()
{
    return this->RightPanelColor;
}

const QString& ColorManager::GetTopPanelColor()
{
    return this->TopPanelColor;
}

const QString& ColorManager::GetCenterPanelBottomColor()
{
    return this->CenterPanelBottomColor;
}
