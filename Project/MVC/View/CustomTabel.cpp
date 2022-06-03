#include "CustomTabel.h"
#include <QGridLayout>
#include <QPainter>

CustomTabel::CustomTabel(QWidget *parent)
    : QWidget{parent}
    , _index(2)
{
    setLayout(new QGridLayout);
    setContentsMargins(0, 0, 0, 0);

    QLabel *title = new QLabel("STATISTICAL TABLE");
    QLabel *started = new QLabel("Launched By");
    QLabel *status = new QLabel("Status");
    QLabel *created = new QLabel("Creator");
    QLabel *createdDate = new QLabel("Deploy Date");
    QLabel *startedDate = new QLabel("Start Date");

    QFont font;
    font.setBold(true);
    title->setFixedHeight(40);
    started->setFixedHeight(40);
    status->setFixedHeight(40);
    created->setFixedHeight(40);
    createdDate->setFixedHeight(40);
    startedDate->setFixedHeight(40);

    title->setFont(font);
    started->setFont(font);
    status->setFont(font);
    created->setFont(font);
    createdDate->setFont(font);
    startedDate->setFont(font);

    title->setStyleSheet("color: rgb(245, 245, 245);");
    started->setStyleSheet("color: rgb(245, 245, 245);");
    status->setStyleSheet("color: rgb(245, 245, 245);");
    created->setStyleSheet("color: rgb(245, 245, 245);");
    createdDate->setStyleSheet("color: rgb(245, 245, 245);");
    startedDate->setStyleSheet("color: rgb(245, 245, 245);");

    ((QGridLayout*)layout())->addWidget(title, 0, 0);
    ((QGridLayout*)layout())->addWidget(started, 1, 0);
    ((QGridLayout*)layout())->addWidget(status, 1, 1);
    ((QGridLayout*)layout())->addWidget(created, 1, 2);
    ((QGridLayout*)layout())->addWidget(createdDate, 1, 3);
    ((QGridLayout*)layout())->addWidget(startedDate, 1, 4);
}

void CustomTabel::AddLine(QString launch, QString status, QString creator, QString deployTime, QString startedTime)
{
    StatisticLine *line = new StatisticLine{new QLabel, new QFrame, new QLabel, new QLabel, new QLabel, new QLabel};
    line->post_time->setText(deployTime);
    line->start_time->setText(startedTime);
    line->indicatorLabel->setText(status);
    line->who_launched->setText(launch);
    line->who_launched->setEnabled(false);
    line->who_created->setText(creator);
    line->indicator->setStyleSheet("background-image: url(:/Image/status_idle.png);"
                                   "background-position: center;"
                                   "background-repeat: no-repeat;");
    if (status == "Idle")
    {
        line->indicator->setStyleSheet("background-image: url(:/Image/status_idle.png);"
                                       "background-position: center;"
                                       "background-repeat: no-repeat;");
    }
    else if (status == "Wait")
    {
        line->indicator->setStyleSheet("background-image: url(:/Image/status_waitwork.png);"
                                       "background-position: center;"
                                       "background-repeat: no-repeat;");
    }
    else if (status == "Working")
    {
        line->indicator->setStyleSheet("background-image: url(:/Image/status_working.png);"
                                       "background-position: center;"
                                       "background-repeat: no-repeat;");
    }
    else if (status == "Failed")
    {
        line->indicator->setStyleSheet("background-image: url(:/Image/status_failed.png);"
                                       "background-position: center;"
                                       "background-repeat: no-repeat;");
    }
    else if (status == "Success")
    {
        line->indicator->setStyleSheet("background-image: url(:/Image/status_success.png);"
                                       "background-position: center;"
                                       "background-repeat: no-repeat;");
    }
    line->indicator->setFixedSize(10, 10);

    line->post_time->setFixedHeight(40);
    line->start_time->setFixedHeight(40);
    line->who_launched->setFixedHeight(40);
    line->who_created->setFixedHeight(40);

    line->post_time->setStyleSheet("color: #95979C;");
    line->start_time->setStyleSheet("color: #95979C;");
    line->indicatorLabel->setStyleSheet("color: #95979C;");
    line->who_launched->setStyleSheet("color: #95979C;");
    line->who_created->setStyleSheet("color: #95979C;");

    ((QGridLayout*)layout())->addWidget(line->who_launched, 20 - this->_index, 0);
    QWidget *widget = new QWidget;
    widget->setLayout(new QHBoxLayout);
    widget->layout()->setContentsMargins(0, 0, 0, 0);
    widget->setFixedHeight(40);
    widget->layout()->addWidget(line->indicator);
    widget->layout()->addWidget(line->indicatorLabel);
    ((QGridLayout*)layout())->addWidget(widget, 20 - this->_index, 1);
    ((QGridLayout*)layout())->addWidget(line->who_created, 20 - this->_index, 2);
    ((QGridLayout*)layout())->addWidget(line->post_time, 20 - this->_index, 3);
    ((QGridLayout*)layout())->addWidget(line->start_time, 20 - this->_index, 4);

    this->_lines.append(std::make_pair(this->_index++, line));
}

void CustomTabel::ChangeStatusOnTop(QString status)
{
    if (!this->_lines.isEmpty())
    {
        for (auto it = this->_lines.begin(); it != this->_lines.end(); it++)
        {
            if (it->first == this->_index - 1)
            {
                if (status == "Idle")
                {
                    it->second->indicator->setStyleSheet("background-image: url(:/Image/status_idle.png);"
                                                   "background-position: center;"
                                                   "background-repeat: no-repeat;");
                }
                else if (status == "Wait")
                {
                    it->second->indicator->setStyleSheet("background-image: url(:/Image/status_waitwork.png);"
                                                   "background-position: center;"
                                                   "background-repeat: no-repeat;");
                }
                else if (status == "Working")
                {
                    it->second->indicator->setStyleSheet("background-image: url(:/Image/status_working.png);"
                                                   "background-position: center;"
                                                   "background-repeat: no-repeat;");
                }
                else if (status == "Failed")
                {
                    it->second->indicator->setStyleSheet("background-image: url(:/Image/status_failed.png);"
                                                   "background-position: center;"
                                                   "background-repeat: no-repeat;");
                }
                else if (status == "Success")
                {
                    it->second->indicator->setStyleSheet("background-image: url(:/Image/status_success.png);"
                                                   "background-position: center;"
                                                   "background-repeat: no-repeat;");
                }
                it->second->indicatorLabel->setText(status);
                break;
            }
        }
    }
}

void CustomTabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#2F3136"));

    painter.drawRoundedRect(rect(), 10, 10);
}
