#ifndef COMPUTERCONTROLLER_H
#define COMPUTERCONTROLLER_H

#include "../Model/Computer.h"
#include "../View/Button/ComputerButton.h"

#include <QObject>
#include <QDomDocument>
#include <QDomElement>

class ComputerController : public QObject
{
    Q_OBJECT
public:
    static ComputerController& Instance();

    void LoadComputer(QDomElement&);
    QList<std::pair<Computer*, ComputerButton*>>& GetComputers();
    bool IsValid();
    void Clean();
    void AddComputer(QString, QString);
    void AddTaskToActiveComputer(QString, QString);
    ComputerButton* GetActiveComputerButton();

private:
    explicit ComputerController(QObject *parent = nullptr);
    ComputerController(const ComputerController&) = delete;
    ComputerController& operator=(const ComputerController&) = delete;

private slots:
    void ComputerButtonClicked(ComputerButton*);

private:
    QList<std::pair<Computer*, ComputerButton*>> _computers;
};

#endif // COMPUTERCONTROLLER_H
