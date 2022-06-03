#include "SectionButton.h"

SectionButton::SectionButton(QWidget *parent)
    : QWidget{parent}
    , _selectedOffset(5)
    , _activeSection(0)
{
    this->_animation = new QPropertyAnimation(this);
    this->_animation->setTargetObject(this);
}

SectionButton::~SectionButton()
{
    if (this->_animation)
        delete this->_animation;
}

void SectionButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QColor("#fff"));
    painter.setBrush(QColor("#E8EAEC"));
    painter.drawRoundedRect(QRectF(0,
                                   0,
                                   width(),
                                   height()),
                            5,
                            5);

    painter.setBrush(QColor("#FFFEFF"));
    painter.drawRoundedRect(QRectF(this->_selectedOffset,
                                   5,
                                   (width() - 10) / this->_sections.size() - 1,
                                   height() - 10),
                            3,
                            3);

    for (int i = 0; i < this->_sections.size(); i++)
    {
        painter.setPen(this->_sections[i].isSelected ? QColor("#1111111") : QColor("#969899"));
        QFont font(this->_fontFamily, 11);
        QFontMetrics metrics(font);
        int xPos = this->_sections[i].x + this->_sections[i].width / 2 - (this->_sections[i].text.size() * 6) / 2;
        if (this->_sections[i].text.size() > 4)
        {
            xPos += 2;
        }
        else
        {
            xPos -= 2;
        }
        painter.drawText(xPos,
                         this->_sections[i].y + this->_sections[i].height / 2 + 5,
                         this->_sections[i].text);
    }
}

void SectionButton::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        for (int i = 0; i < this->_sections.size(); i++)
        {
            if (event->pos().x() > this->_sections[i].x
                    && event->pos().x() < this->_sections[i].x + this->_sections[i].width)
            {
                if (!this->_sections[i].isSelected)
                {
                    this->_sections[i].isSelected = true;
                    for (int j = 0; j < this->_sections.size(); j++)
                    {
                        if (i != j)
                        {
                            this->_sections[j].isSelected = false;
                        }
                    }

                    this->_animation->setDuration(180);
                    if (this->_animation->state() != QPropertyAnimation::Running)
                    {
                        this->_animation->setPropertyName("_selectedOffset");
                    }
                    this->_animation->setStartValue(this->_selectedOffset);
                    this->_animation->setEndValue(this->_sections[i].x);
                    this->_animation->start();
                    this->_activeSection = this->_sections[i].id;
                    emit selectionChanged(this->_sections[i].id);
                    repaint();
                }
                break;
            }
        }
    }
}

void SectionButton::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int items = this->_sections.size();
    int borderWidth = 10;
    int newItemWidth = (event->size().width() - borderWidth) / items;
    int startsX = 5;
    int positionId = 0;
    for (auto it = this->_sections.begin(); it != this->_sections.end(); it++)
    {
        (*it).id = positionId++;
        (*it).x = startsX;
        (*it).width = newItemWidth - 1;
        (*it).y = 5;
        (*it).height = event->size().height() - 10;
        startsX += newItemWidth +1;
    }
    setSelected(this->_activeSection);
    update();
}

int SectionButton::createSection(QString selectionText, int position)
{
    int items = this->_sections.size() + 1;
    int borderWidth = 10;
    int newItemWidth = (width() - borderWidth) / items;

    if (position == -1)
    {
        this->_sections.append(SectionItem{0, 0, 0, 0, 0, selectionText, false});
    }
    else
    {
        if (position < this->_sections.size())
        {
            this->_sections.insert(position, SectionItem{0, 0, 0, 0, 0, selectionText, false});

        }
        else
        {
            throw std::exception();
        }
    }

    int startsX = 5;
    int positionId = 0;
    for (auto it = this->_sections.begin(); it != this->_sections.end(); it++)
    {
        (*it).id = positionId++;
        (*it).x = startsX;
        (*it).width = newItemWidth - 1;
        (*it).y = 5;
        (*it).height = height() - 10;
        startsX += newItemWidth +1;
    }
}

void SectionButton::setSelected(int index)
{
    if (index >= 0 && index < this->_sections.size())
    {
        for (int i = 0; i < this->_sections.size(); i++)
        {
            if (index != i)
            {
                this->_sections[i].isSelected = false;
            }
        }
        this->_sections[index].isSelected = true;
        this->_activeSection = index;
        this->_selectedOffset = this->_sections[index].x;
    }
    else
    {
        throw std::exception();
    }
}

void SectionButton::setSelectedOffset(int value)
{
    this->_selectedOffset = value;
    update();
}

int SectionButton::getSelectedOffset()
{
    return this->_selectedOffset;
}

void SectionButton::setFontFamily(QString family)
{
    this->_fontFamily = family;
}

int SectionButton::GetActiveSection()
{
    return this->_activeSection;
}
