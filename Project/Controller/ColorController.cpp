#include "ColorController.h"

ColorController::ColorController()
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

ColorController::~ColorController()
{

}

ColorController &ColorController::Instance()
{
    static ColorController instance;
    return instance;
}

const ColorController::ButtonColors& ColorController::GetComputerButtonColors()
{
    return this->ComputerButtonColor;
}

const ColorController::ButtonColors& ColorController::GetTaskButtonColors()
{
    return this->TaskButtonColor;
}

const ColorController::ButtonColors& ColorController::GetTaskButtonCloseButtonColors()
{
    return this->TaskButtonCloseButtonColor;
}

const QString& ColorController::GetLeftPanelColor()
{
    return this->LeftPanelColor;
}

const QString& ColorController::GetCenterPanelColor()
{
    return this->CenterPanelColor;
}

const QString& ColorController::GetRightPanelColor()
{
    return this->RightPanelColor;
}

const QString& ColorController::GetTopPanelColor()
{
    return this->TopPanelColor;
}

const QString& ColorController::GetCenterPanelBottomColor()
{
    return this->CenterPanelBottomColor;
}
