#include "ComputerController.h"
#include "Manager/NetworkManager.h"
#include "TaskController.h"
#include "../../Window/ProgramWindow.h"
#include <QDebug>

ComputerController::ComputerController(QObject *parent)
    : QObject{parent}
{
    qDebug() << "[CREATED]" << this;
}

ComputerController::~ComputerController()
{
    qDebug() << "[DELETED]" << this;
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        delete it->first;
    }
}

ComputerController& ComputerController::Instance()
{
    static ComputerController instance;
    return instance;
}

void ComputerController::LoadComputer(QDomElement &document)
{
    // computer attributes
    Computer *computer = new Computer;
    computer->SetName(document.attribute("Name", ""));
    computer->SetIP(document.attribute("IP", ""));
    computer->SetMAC(document.attribute("MAC", ""));
    computer->SetUniqueID(document.attribute("UniqueID", ""));

    // computer button
    ComputerButton *computerButton = new ComputerButton();
    computerButton->SetImage(":/Image/icon_machine.svg");
    computerButton->SetComputer(computer);
    connect(computerButton, &ComputerButton::clicked, this, &ComputerController::ComputerButtonClicked);
    if (computer->GetUniqueID() == NetworkManager::Instance().GetThisMachineUniqueID())
    {
        computer->SetIP(NetworkManager::Instance().GetThisMachineIP());
        computer->SetIsThisComputer(true);
        computerButton->SetFocused(true);
        ProgramWindow::Instance().SetComputerInfo(computer->GetName(), computer->GetIP());
    }
    ProgramWindow::Instance().AddComputerButton(computerButton);

    // tasks
    QDomElement taskElement = document.firstChild().toElement();
    while (!taskElement.isNull())
    {
        if (taskElement.tagName() == "Task")
        {
            std::pair<Task*, TaskButton*> pair = TaskController::Instance().LoadTask(taskElement);
            computer->AddTask(pair.first);
            ProgramWindow::Instance().AddTaskByIndex(computerButton->GetStackedIndex(), pair.second);
        }
        taskElement = taskElement.nextSibling().toElement();
    }

    // save computers
    this->_computers.append(std::make_pair(computer, computerButton));
}

QList<std::pair<Computer*, ComputerButton*>>& ComputerController::GetComputers()
{
    return this->_computers;
}

void ComputerController::ComputerButtonClicked(ComputerButton *button)
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (it->second != button)
        {
            it->second->SetFocused(false);
        }
        else
        {
            ProgramWindow::Instance().SetActiveTaskWidget(it->second->GetStackedIndex());
            ProgramWindow::Instance().SetComputerInfo(it->first->GetName(), it->first->GetIP());
        }
    }
}

bool ComputerController::IsValid()
{
    bool hasThisComputer = false;
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (it->first->GetUniqueID() == NetworkManager::Instance().GetThisMachineUniqueID())
        {
            hasThisComputer = true;
            break;
        }
    }
    if (!hasThisComputer || this->_computers.isEmpty())
    {
        Computer *computer = new Computer;
        computer->SetName(NetworkManager::Instance().GetThisMachineName());
        computer->SetIP(NetworkManager::Instance().GetThisMachineIP());
        computer->SetMAC(NetworkManager::Instance().GetThisMachineMAC());
        computer->SetUniqueID(NetworkManager::Instance().GetThisMachineUniqueID());

        this->_computers.append(std::make_pair(computer, nullptr));
        return false;
    }

    return true;
}

void ComputerController::Clean()
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (it->first != nullptr)
            delete it->first;
        if (it->second != nullptr)
            delete it->second;
    }
    this->_computers.clear();
}

void ComputerController::AddComputer(QString name, QString ip)
{
    Computer *computer = new Computer;
    computer->SetName(name);
    computer->SetIP(ip);

    ComputerButton *computerButton = new ComputerButton();
    computerButton->SetImage(":/Image/icon_machine.svg");
    computerButton->SetComputer(computer);
    connect(computerButton, &ComputerButton::clicked, this, &ComputerController::ComputerButtonClicked);
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        it->second->SetFocused(false);
    }
    computerButton->SetFocused(true);
    ProgramWindow::Instance().AddComputerButton(computerButton);
    ProgramWindow::Instance().AddTaskByIndex(computerButton->GetStackedIndex(), nullptr);
    ProgramWindow::Instance().SetActiveTaskWidget(computerButton->GetStackedIndex());

    this->_computers.append(std::make_pair(computer, computerButton));
}

void ComputerController::AddTaskToActiveComputer(QString name, QString id)
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (it->second->IsFocused())
        {
            Task *task = new Task;
            task->SetName(name);
            task->SetID(id);
            it->first->AddTask(task);
            ProgramWindow::Instance().AddTaskByIndex(it->second->GetStackedIndex(), TaskController::Instance().AddTask(task));
            ProgramWindow::Instance().SetActiveTaskWidget(it->second->GetStackedIndex());
            break;
        }
    }
}

ComputerButton* ComputerController::GetActiveComputerButton()
{
    for (auto it = this->_computers.begin(); it != this->_computers.end(); it++)
    {
        if (it->second->IsFocused())
        {
            return it->second;
        }
    }
}
