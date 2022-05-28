#ifndef COMPUTERSCONTROLLER_H
#define COMPUTERSCONTROLLER_H

#include <QMap>
#include <QDomDocument>

#include "../Model/Computer.h"
#include "../View/Buttons/ComputerButton.h"
#include "../View/Buttons/TaskButton.h"

class ComputersController final : public QWidget
{
    Q_OBJECT
private:
    ComputersController();
    ~ComputersController();
    ComputersController(const ComputersController&) = delete;
    ComputersController& operator=(const ComputersController&) = delete;

public:
    static ComputersController &Instance();

    void LoadComputer(QDomElement& document);
    void CheckValidInfo();

    const QList<std::pair<Computer*, ComputerButton*>> *GetComputerButtons();
    const QList<std::pair<Computer*, QList<std::pair<Task*, TaskButton*>>*>> *GetTasks();
    const QList<std::pair<Task*, TaskButton*>> *GetActiveComputerTaskButtons();

    void AddTaskToActiveComputer(QString, QString);
    void AddComputer(QString, QString);
    void ReGenerateTaskButtonsByComputer(Computer*);

private slots:
    void ComputerButtonClicked(ComputerButton*);
    void TaskButtonClicked(TaskButton*);

private:
    QList<std::pair<Computer*, ComputerButton*>> *_computerButtons;
    QList<std::pair<Computer*, QList<std::pair<Task*, TaskButton*>>*>> *_tasks;
};

#endif // COMPUTERSCONTROLLER_H
