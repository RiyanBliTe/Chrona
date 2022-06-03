#include "Starter.h"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include "../Controller/TaskController.h"
#include "../Controller/PipelineController.h"
#include "../../Window/ProgramWindow.h"

Starter::Starter(QObject *parent)
    : QObject{parent}
    , _Pipeline(nullptr)
    , _mainProcess(nullptr)
    , _fileIndex(0)
    , _hasError(false)
    , _task(nullptr)
    , _file(nullptr)
{
    this->_mainProcess = new QProcess;
    this->_timer = new QTimer;
    this->_timer->setSingleShot(true);

    if (!QFileInfo::exists("Data/Logs"))
    {
        QDir dir;
        dir.mkdir("Data/Logs");
    }

    connect(this->_mainProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Starter::OnFinished);
    connect(this->_mainProcess, &QProcess::errorOccurred, this, &Starter::OnErrorOccured);
    connect(this->_mainProcess, &QProcess::stateChanged, this, &Starter::OnStateChanged);
    connect(this->_mainProcess, &QProcess::readyReadStandardError, this, &Starter::OnReadyReadStandardError);
    connect(this->_mainProcess, &QProcess::readyReadStandardOutput, this, &Starter::OnReadyReadStandardOutput);
    connect(this->_timer, &QTimer::timeout, [this]()
    {
        Start();
    });
}

Starter::~Starter()
{}

void Starter::SetPipeline(Pipeline *pipeline)
{
    this->_Pipeline = pipeline;
}

void Starter::SetTask(Task *task)
{
    this->_task = task;
}

void Starter::Start()
{
    if (this->_Pipeline != nullptr && this->_Pipeline->GetFiles().size() != 0 && this->_Pipeline->GetFiles().size() > this->_fileIndex)
    {
        if (this->_file == nullptr)
        {
            int index = 0;
            for (int i = 0; i < this->_task->GetPipelines().size(); i++)
                if (this->_task->GetPipelines().at(i) == this->_Pipeline)
                {
                    index = i;
                    break;
                }

            this->_file = new QFile(QString("Data/Logs/log_%1_pipeline_%2_%3.txt").arg(this->_task->GetName(),
                                                                                       std::to_string(index).c_str(),
                                                                                       this->_task->GetStartDateTime().toString("dd.MM.yyyy_hh.mm.ss")));
            this->_file->open(QIODevice::ReadWrite | QFile::Append);
        }

        CustomFile *file = this->_Pipeline->GetFiles().at(this->_fileIndex++);
        QString preRun = file->GetPreRunArguments();
        QString runArg = file->GetRunArguments();
        QString fileName = file->GetName();
        QFileInfo info(file->GetPath());
        QString directory = info.absolutePath();
        int condition = file->GetIndexType();

        // 0 - after prev
        // 1 - if prev
        // 2 - if !prev
        if (condition == 0 || (condition == 1 && !this->_hasError) || (condition == 2 && this->_hasError))
        {
            this->_file->write("---------------------------------------------------------------------------------------\n");
            this->_file->write(QString("File: %1\n").arg(this->_Pipeline->GetFiles().at(this->_fileIndex-1)->GetPath()).toStdString().c_str());
            this->_file->write("\n");

            this->_hasError = false;
            this->_mainProcess->setWorkingDirectory(directory);
            this->_mainProcess->setArguments(runArg.split(" "));
            if (info.suffix().contains("exe"))
            {
                if (this->_mainProcess->startDetached(preRun + "\"" + file->GetPath() + "\"" + runArg))
                {
                    this->_Pipeline->SetFinished(true);
                    emit workFinished(this);
                }
                else
                {
                    this->_Pipeline->SetFinished(false);
                    emit workFinished(this);
                }
            }
            else
                this->_mainProcess->start(preRun + " " + fileName);
        }
        else
        {
            if (this->_Pipeline->GetFiles().size() > this->_fileIndex ||
                    this->_Pipeline->GetFiles().at(this->_fileIndex - 1)->GetStatus() == false ||
                    (this->_fileIndex - 2 >= 0 && this->_Pipeline->GetFiles().at(this->_fileIndex - 1) == file && this->_Pipeline->GetFiles().at(this->_fileIndex - 2)->GetStatus() == false))
            {
                this->_Pipeline->SetFinished(false);
            }
            else
            {
                this->_Pipeline->SetFinished(true);
            }
            PipelineController::Instance().Update();
            this->_file->close();
            emit workFinished(this);
        }
    }
    else
    {
        if (this->_Pipeline != nullptr && this->_Pipeline->GetFiles().size() != 0 && this->_Pipeline->GetFiles().size() == this->_fileIndex)
        {
            if (this->_Pipeline->GetFiles().at(this->_fileIndex - 1)->GetStatus())
            {
                this->_Pipeline->SetFinished(true);
            }
            else
            {
                this->_Pipeline->SetFinished(false);
            }
            PipelineController::Instance().Update();
            this->_file->close();
            emit workFinished(this);
        }
    }
}

void Starter::OnErrorOccured(QProcess::ProcessError error)
{
    this->_hasError = true;
    this->_Pipeline->GetFiles().at(this->_fileIndex - 1)->SetStatus(false);
    this->_timer->start(1000);
    //qDebug() << "OnErrorOccured: " << error;
}

void Starter::OnStateChanged(QProcess::ProcessState newState)
{
    //qDebug() << "OnStateChanged: " << newState;
}

void Starter::OnFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    CustomFile *file = this->_Pipeline->GetFiles().at(this->_fileIndex - 1);
    if (this->_Pipeline->GetFiles().at(this->_fileIndex - 1)->GetStatus())
        this->_timer->start(1000);
    //qDebug() << "OnFinished: " << this->_fileIndex << exitCode << " : " << exitStatus;
}

void Starter::OnReadyReadStandardError()
{
    this->_hasError = true;
    this->_Pipeline->GetFiles().at(this->_fileIndex - 1)->SetStatus(false);
    QString a = this->_mainProcess->readAllStandardError().toStdString().c_str();
    this->_file->write(a.toStdString().c_str());
    this->_timer->start(1000);
    //qDebug() << "OnReadyReadStandardError: ";// << this->_mainProcess->readAllStandardError().toStdString().c_str();
}

void Starter::OnReadyReadStandardOutput()
{
    QString a = this->_mainProcess->readAllStandardOutput().toStdString().c_str();
    this->_file->write(a.toStdString().c_str());
    //qDebug() << "OnReadyReadStandardOutput: ";// << this->_mainProcess->readAllStandardOutput().toStdString().c_str();
}
