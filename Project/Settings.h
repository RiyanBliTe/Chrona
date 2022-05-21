#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDebug>
#include <QFontDatabase>

class Settings final
{
public:
    static Settings &GetInstance()
    {
        static Settings _instance;
        return _instance;
    }

private:
    Settings()
        : _left_panel_background_color("#202225")
        , _on_left_panel_enter_color("#76B39D")
        , _on_left_panel_idle_color("#36393F")
        , _on_left_panel_press_color("#589E85")
        , _on_left_panel_border_color("#ffffff")
        , _center_panel_background_center_color("#2F3136")
        , _center_panel_background_bottom_color("#292B2F")
        , _on_center_panel_task_button_enter_color("#3C3F45")
        , _on_center_panel_task_button_idle_color("#2F3136")
        , _on_center_panel_task_button_press_color("#3F4248")
        , _on_center_panel_task_button_text_color("#96989D")
        , _on_center_panel_task_button_close_button_enter_color("#151617")
        , _on_center_panel_task_button_close_button_idle_color("#2F3136")
        , _on_center_panel_task_button_close_button_press_color("#76B39D")
        , _right_panel_background_color("#36393F")
        , _top_panel_menubutton_enter_color("#40444B")
        , _top_panel_menubutton_idle_color("#36393F")
        , _top_panel_menubutton_press_color("#454950")
        , _top_panel_menubutton_text_color("#B9BBBE")
        , _sen_regular_id(-1)
        , _sen_bold_id(-1)
        , _sen_extrabold_id(-1)
    {};
    ~Settings(){};
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

public:
    enum class Fonts
    {
        SEN_REGULAR,
        SEN_BOLD,
        SEN_EXTRABOLD
    };

    QString GetApplicationFont(Fonts value)
    {
        switch (value)
        {
        case Settings::Fonts::SEN_REGULAR:
            return QFontDatabase::applicationFontFamilies(_sen_regular_id).at(0);
            break;
        case Settings::Fonts::SEN_BOLD:
            return QFontDatabase::applicationFontFamilies(_sen_bold_id).at(0);
            break;
        case Settings::Fonts::SEN_EXTRABOLD:
            return QFontDatabase::applicationFontFamilies(_sen_extrabold_id).at(0);
            break;
        }
        return "";
    }

    void SetSenFontIds(int id_regular, int id_bold, int id_extrabold)
    {
        this->_sen_regular_id = id_regular;
        this->_sen_bold_id = id_bold;
        this->_sen_extrabold_id = id_extrabold;
    }

public:
    // Left Panel
    QString _left_panel_background_color;
    QString _on_left_panel_enter_color;
    QString _on_left_panel_idle_color;
    QString _on_left_panel_press_color;
    QString _on_left_panel_border_color;

    // Center Panel
    QString _center_panel_background_center_color;
    QString _center_panel_background_bottom_color;
    QString _on_center_panel_task_button_enter_color;
    QString _on_center_panel_task_button_idle_color;
    QString _on_center_panel_task_button_press_color;
    QString _on_center_panel_task_button_text_color;
    QString _on_center_panel_task_button_close_button_enter_color;
    QString _on_center_panel_task_button_close_button_idle_color;
    QString _on_center_panel_task_button_close_button_press_color;

    // Right Panel
    QString _right_panel_background_color;

    // Top Panel
    QString _top_panel_menubutton_enter_color;
    QString _top_panel_menubutton_idle_color;
    QString _top_panel_menubutton_press_color;
    QString _top_panel_menubutton_text_color;

private:
    int _sen_regular_id;
    int _sen_bold_id;
    int _sen_extrabold_id;
};

#endif // SETTINGS_H
