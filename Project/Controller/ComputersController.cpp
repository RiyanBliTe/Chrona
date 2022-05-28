#include "ComputersController.h"
#include "NetworkController.h"
#include "../View/ProgramWindow.h"

ComputersController::ComputersController()
{
    this->_computerButtons = new QList<std::pair<Computer*, ComputerButton*>>();
    this->_tasks = new QList<std::pair<Computer*, QList<std::pair<Task*, TaskButton*>>*>>();
}

ComputersController::~ComputersController()
{
    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->first)
        {
            delete it->first;
        }
    }

    for (auto it = this->_tasks->begin(); it != this->_tasks->end(); it++)
    {
        if (it->second)
        {
            delete it->second;
        }
    }

    delete this->_computerButtons;
    delete this->_tasks;
}

ComputersController &ComputersController::Instance()
{
    static ComputersController instance;
    return instance;
}

void ComputersController::LoadComputer(QDomElement& document)
{
    // attributes
    Computer *computer = new Computer();
    computer->SetName(document.attribute("Name", ""));
    computer->SetIP(document.attribute("IP", ""));
    computer->SetMAC(document.attribute("MAC", ""));
    computer->SetUniqueID(document.attribute("UniqueID", ""));

    // computer button
    ComputerButton *computerButton = new ComputerButton();
    computerButton->SetImage(":/images/Images/icon_machine.svg");
    connect(computerButton, &ComputerButton::clicked, this, &ComputersController::ComputerButtonClicked);
    if (computer->GetUniqueID() == NetworkController::Instance().GetThisMachineUniqueID())
    {
        computer->SetIP(NetworkController::Instance().GetThisMachineIP());
        computer->SetIsThisComputer(true);
        computerButton->SetFocused(true);
    }

    // tasks
    QDomElement taskElement = document.firstChild().toElement();
    QList<std::pair<Task*, TaskButton*>> *tasks = new QList<std::pair<Task*, TaskButton*>>();
    while (!taskElement.isNull())
    {
        if (taskElement.tagName() == "Task")
        {
            Task *task = new Task();
            task->SetID(taskElement.attribute("ID", ""));
            task->SetName(taskElement.attribute("Name", ""));

            TaskButton *taskButton = new TaskButton();
            taskButton->SetText(task->GetName());
            connect(taskButton, &TaskButton::clicked, this, &ComputersController::TaskButtonClicked);
            tasks->append(std::make_pair(task, taskButton));
        }
        taskElement = taskElement.nextSibling().toElement();
    }

    this->_computerButtons->append(std::make_pair(computer, computerButton));
    this->_tasks->append(std::make_pair(computer, tasks));
}

void ComputersController::CheckValidInfo()
{
    if (this->_computerButtons->isEmpty())
    {
        Computer *computer = new Computer();
        computer->SetName(NetworkController::Instance().GetThisMachineName());
        computer->SetIP(NetworkController::Instance().GetThisMachineIP());
        computer->SetMAC(NetworkController::Instance().GetThisMachineMAC());
        computer->SetUniqueID(NetworkController::Instance().GetThisMachineUniqueID());

        ComputerButton *computerButton = new ComputerButton();
        computerButton->SetImage(":/images/Images/icon_machine.svg");
        connect(computerButton, &ComputerButton::clicked, this, &ComputersController::ComputerButtonClicked);
        computer->SetIsThisComputer(true);
        computerButton->SetFocused(true);

        this->_computerButtons->append(std::make_pair(computer, computerButton));
        this->_tasks->append(std::make_pair(computer, new QList<std::pair<Task*, TaskButton*>>()));
    }

    bool hasThisComputer = false;
    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->first->GetUniqueID() == NetworkController::Instance().GetThisMachineUniqueID())
            hasThisComputer = true;
    }
    if (!hasThisComputer)
    {
        Computer *computer = new Computer();
        computer->SetName(NetworkController::Instance().GetThisMachineName());
        computer->SetIP(NetworkController::Instance().GetThisMachineIP());
        computer->SetMAC(NetworkController::Instance().GetThisMachineMAC());
        computer->SetUniqueID(NetworkController::Instance().GetThisMachineUniqueID());

        ComputerButton *computerButton = new ComputerButton();
        computerButton->SetImage(":/images/Images/icon_machine.svg");
        connect(computerButton, &ComputerButton::clicked, this, &ComputersController::ComputerButtonClicked);
        computer->SetIsThisComputer(true);
        computerButton->SetFocused(true);

        this->_computerButtons->prepend(std::make_pair(computer, computerButton));
        this->_tasks->prepend(std::make_pair(computer, new QList<std::pair<Task*, TaskButton*>>()));
    }
}

const QList<std::pair<Computer*, ComputerButton*>> *ComputersController::GetComputerButtons()
{
    return this->_computerButtons;
}

const QList<std::pair<Computer*, QList<std::pair<Task*, TaskButton*>>*>> *ComputersController::GetTasks()
{
    return this->_tasks;
}

const QList<std::pair<Task*, TaskButton*>> *ComputersController::GetActiveComputerTaskButtons()
{
    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->second->IsFocused())
        {
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    return it2->second;
                }
            }
            break;
        }
    }
    return nullptr;
}

void ComputersController::ComputerButtonClicked(ComputerButton *button)
{
    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->second->IsFocused())
        {
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    ReGenerateTaskButtonsByComputer(it2->first);
                    break;
                }
            }
        }
        if (it->second != button)
        {
            it->second->SetFocused(false);
        }
        else
        {
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    ProgramWindow::Instance().ChangeComputerData(it2->first->GetName(), it2->first->GetIP());
                    ProgramWindow::Instance().LoadTasksListToForm(it2->second);
                    break;
                }
            }
        }
    }
}

void ComputersController::TaskButtonClicked(TaskButton *button)
{
    bool isLock = false;
    for (auto it = this->_tasks->begin(); it != this->_tasks->end(); it++)
    {
        for (auto it2 = it->second->begin(); it2 != it->second->end(); it2++)
        {
            if (!isLock && it2->second == button)
            {
                it2 = it->second->begin();
                isLock = true;
            }
            if (isLock && it2->second != button)
            {
                it2->second->SetFocused(false);
            }
        }
        if (isLock)
            break;
    }
}

void ComputersController::AddTaskToActiveComputer(QString task_name, QString task_id)
{
    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->second->IsFocused())
        {
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    Task *task = new Task();
                    task->SetName(task_name);
                    task->SetID(task_id);

                    TaskButton *taskButton = new TaskButton();
                    taskButton->SetText(task_name);
                    connect(taskButton, &TaskButton::clicked, this, &ComputersController::TaskButtonClicked);
                    it2->second->append(std::make_pair(task, taskButton));
                    break;
                }
            }
        }
    }

    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->second->IsFocused())
        {
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    for (auto it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
                    {
                        it3->second->SetFocused(false);
                    }
                    ReGenerateTaskButtonsByComputer(it2->first);
                    (--it2->second->end())->second->SetFocused(true);
                    break;
                }
            }
        }
    }
    ProgramWindow::Instance().LoadTasksListToForm(GetActiveComputerTaskButtons());
}

void ComputersController::AddComputer(QString name, QString ip)
{
    Computer *computer = new Computer();
    computer->SetName(name);
    computer->SetIP(ip);

    ComputerButton *computerButton = new ComputerButton();
    computerButton->SetImage(":/images/Images/icon_machine.svg");
    connect(computerButton, &ComputerButton::clicked, this, &ComputersController::ComputerButtonClicked);

    for (auto it = this->_computerButtons->begin(); it != this->_computerButtons->end(); it++)
    {
        if (it->second->IsFocused())
        {
            it->second->SetFocused(false);
            for (auto it2 = this->_tasks->begin(); it2 != this->_tasks->end(); it2++)
            {
                if (it2->first == it->first)
                {
                    ReGenerateTaskButtonsByComputer(it2->first);
                    break;
                }
            }
        }
    }

    computerButton->SetFocused(true);
    ProgramWindow::Instance().AddCompterToTorm(computerButton);

    this->_computerButtons->append(std::make_pair(computer, computerButton));
    QList<std::pair<Task*, TaskButton*>> *list = new QList<std::pair<Task*, TaskButton*>>();
    this->_tasks->append(std::make_pair(computer, list));
    ProgramWindow::Instance().LoadTasksListToForm(list);
}

void ComputersController::ReGenerateTaskButtonsByComputer(Computer *computer)
{
    for (auto it = this->_tasks->begin(); it != this->_tasks->end(); it++)
    {
        if (it->first == computer)
        {
            for (auto it2 = it->second->begin(); it2 != it->second->end(); it2++)
            {
                TaskButton *taskButton = new TaskButton();
                taskButton->SetText(it2->first->GetName());
                taskButton->SetFocused(it2->second->IsFocused());
                connect(taskButton, &TaskButton::clicked, this, &ComputersController::TaskButtonClicked);
                delete it2->second;
                it2->second = taskButton;
            }
            break;
        }
    }
}
