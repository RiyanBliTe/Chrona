#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

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
        : _on_left_panel_enter_color("#76B39D")
        , _on_left_panel_idle_color("#36393F")
        , _on_left_panel_press_color("#589E85")
        , _on_left_panel_border_color("#ffffff")
        , _on_center_panel_task_button_enter_color("#3C3F45")
        , _on_center_panel_task_button_idle_color("#2F3136")
        , _on_center_panel_task_button_press_color("#3F4248")
        , _on_center_panel_task_button_text_color("#ffffff")
        , _on_center_panel_task_button_close_button_enter_color("#151617")
        , _on_center_panel_task_button_close_button_idle_color("#2F3136")
        , _on_center_panel_task_button_close_button_press_color("#76B39D")
    {};
    ~Settings(){};
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

public:
    // Left Panel
    QString _on_left_panel_enter_color;
    QString _on_left_panel_idle_color;
    QString _on_left_panel_press_color;
    QString _on_left_panel_border_color;

    // Center Panel
    QString _on_center_panel_task_button_enter_color;
    QString _on_center_panel_task_button_idle_color;
    QString _on_center_panel_task_button_press_color;
    QString _on_center_panel_task_button_text_color;
    QString _on_center_panel_task_button_close_button_enter_color;
    QString _on_center_panel_task_button_close_button_idle_color;
    QString _on_center_panel_task_button_close_button_press_color;
};

#endif // SETTINGS_H
