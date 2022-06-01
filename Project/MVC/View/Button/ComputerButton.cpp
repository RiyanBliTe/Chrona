#include "ComputerButton.h"
#include "../../Controller/Manager/ColorManager.h"
#include <QDebug>

// *************************************************************
// Center Button class
// *************************************************************

CenterButton::CenterButton(QWidget *parent)
    : QAbstractButton(parent)
    , _resizeAnimation(nullptr)
    , _animationOFFSET(0)
    , _pressShift(0)
    , _isFocused(false)
    , _hasImage(false)
    , _isHiden(false)
    , _isPinned(true)
    , _selectedColor(ColorManager::Instance().GetComputerButtonColors().idle)
    , _imagePath("")
{
    SetMemory();
    SetupModules();
}

CenterButton::~CenterButton()
{
    if (this->_resizeAnimation != nullptr)
        delete this->_resizeAnimation;
}

void CenterButton::SetMemory()
{
    if (this->_resizeAnimation == nullptr)
        this->_resizeAnimation = new QPropertyAnimation(this);
}

void CenterButton::SetupModules()
{
    setCheckable(true);
    this->_resizeAnimation->setTargetObject(this);
}

void CenterButton::SetAnimationOFFSET(int value)
{
    this->_animationOFFSET = value;
    update();
}

int CenterButton::GetAnimationOFFSET()
{
    return this->_animationOFFSET;
}

void CenterButton::Hide()
{
    this->_isHiden = true;
    update();
}

void CenterButton::Show()
{
    this->_isHiden = false;
    update();
}

void CenterButton::Pin()
{
    this->_isPinned = true;
}

void CenterButton::UnPin()
{
    this->_isPinned = false;
}

void CenterButton::SetFocused(bool value)
{
    if (!this->_isPinned)
        return;
    this->_isFocused = value;
    if (value)
    {
        this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().enter;
        this->SetAnimationOFFSET(8);
    }
    else
    {
        this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().idle;
        this->SetAnimationOFFSET(0);
    }
    update();
}

bool CenterButton::IsFocused()
{
    return this->_isFocused;
}

void CenterButton::SetImage(QString value)
{
    this->_imagePath = value;
    this->_hasImage = true;
}

QSize CenterButton::sizeHint() const
{
    return QSize(this->ICON_SIZE, this->ICON_SIZE);
}

void CenterButton::enterEvent(QEvent *event)
{
    (void)event;

    if (!this->IsFocused())
    {
        this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().enter;
        emit this->entered();
        this->_resizeAnimation->setDuration(90);
        if (this->_resizeAnimation->state() != QPropertyAnimation::Running)
        {
            this->_resizeAnimation->setPropertyName("_animationOFFSET");
        }
        this->_resizeAnimation->setStartValue(this->_animationOFFSET);
        this->_resizeAnimation->setEndValue(8);
        this->_resizeAnimation->start();
    }
}

void CenterButton::leaveEvent(QEvent *event)
{
    (void)event;

    if (!this->IsFocused())
    {
        if (this->_resizeAnimation->state() == QPropertyAnimation::Running)
        {
            this->_resizeAnimation->stop();
        }
        this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().idle;
        emit this->leaved();
        this->_resizeAnimation->setDuration(90);
        if (this->_resizeAnimation->state() != QPropertyAnimation::Running)
        {
            this->_resizeAnimation->setPropertyName("_animationOFFSET");
        }
        this->_resizeAnimation->setStartValue(this->_animationOFFSET);
        this->_resizeAnimation->setEndValue(0);
        this->_resizeAnimation->start();
    }
}

void CenterButton::mousePressEvent(QMouseEvent *event)
{
    (void)event;

    QAbstractButton::mousePressEvent(event);

    this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().press;
    this->_pressShift = 1;
    update();
}

void CenterButton::mouseReleaseEvent(QMouseEvent *event)
{
    (void)event;

    QAbstractButton::mouseReleaseEvent(event);

    if (this->IsFocused())
        this->_selectedColor = ColorManager::Instance().GetComputerButtonColors().enter;
    this->_pressShift = 0;
    update();
}

void CenterButton::paintEvent(QPaintEvent *event)
{
    (void)event;

    if (!this->_isHiden)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(_selectedColor), 0.1));
        painter.setBrush(QColor(_selectedColor));
        painter.drawRoundedRect(QRectF(0,
                                       1 + this->_pressShift,
                                       this->ICON_SIZE - 2,
                                       this->ICON_SIZE - 2),
                                this->ICON_SIZE / 2 + 2 - this->_animationOFFSET,
                                this->ICON_SIZE / 2 + 2 - this->_animationOFFSET);

        if (this->_hasImage)
        {
            QImage image(this->_imagePath);
            painter.drawImage(QRectF(this->ICON_SIZE / 2 - image.width() / 2 - 1,
                                     this->ICON_SIZE / 2 - image.height() / 2 + this->_pressShift,
                                     image.width(),
                                     image.height()),
                              QImage(image));
        }
    }
}

// *************************************************************
// Border Rounded Rectangle class
// *************************************************************

BorderRoundedRectungle::BorderRoundedRectungle(QWidget *parent)
    : QWidget(parent)
    , _widthAnimation(nullptr)
    , _heightAnimation(nullptr)
    , _needDraw(true)
    , _animClock(false)
    , _isFocused(false)
    , _isHiden(false)
    , _widthOFFSET(4)
    , _heightOFFSET(0)
{
    SetMemory();
    SetupModules();
}

BorderRoundedRectungle::~BorderRoundedRectungle()
{
    if (this->_widthAnimation != nullptr)
        delete this->_widthAnimation;
    if (this->_heightAnimation != nullptr)
        delete this->_heightAnimation;
}

void BorderRoundedRectungle::SetMemory()
{
    if (this->_widthAnimation == nullptr)
        this->_widthAnimation = new QPropertyAnimation(this);
    if (this->_heightAnimation == nullptr)
        this->_heightAnimation = new QPropertyAnimation(this);
}

void BorderRoundedRectungle::SetupModules()
{
    this->setFixedSize(4, this->LEFT_PANEL_HEIGHT_MAX);

    this->_widthAnimation->setTargetObject(this);
    this->_heightAnimation->setTargetObject(this);

    connect(this->_widthAnimation, &QPropertyAnimation::finished, this, &BorderRoundedRectungle::LeaveAnimationFinished);
}

void BorderRoundedRectungle::Hide()
{
    this->_isHiden = true;
}

void BorderRoundedRectungle::Show()
{
    this->_isHiden = false;
}

void BorderRoundedRectungle::LeaveAnimationFinished()
{
    if (this->_animClock)
    {
        this->_needDraw = false;
        update();
    }
}

void BorderRoundedRectungle::StartEnteredAnimation()
{
    this->_animClock = false;
    this->_widthAnimation->setDuration(90);
    if (this->_widthAnimation->state() != QPropertyAnimation::Running)
    {
        this->_widthAnimation->setPropertyName("_widthOFFSET");
    }
    this->_widthAnimation->setStartValue(this->_widthOFFSET);
    this->_widthAnimation->setEndValue(0);
    this->_widthAnimation->start();
}

void BorderRoundedRectungle::StartLeavedAnimation()
{
    if (this->_widthAnimation->state() == QPropertyAnimation::Running)
    {
        this->_widthAnimation->stop();
    }
    this->_widthAnimation->setDuration(90);
    if (this->_widthAnimation->state() != QPropertyAnimation::Running)
    {
        this->_widthAnimation->setPropertyName("_widthOFFSET");
    }
    this->_widthAnimation->setStartValue(this->_widthOFFSET);
    this->_widthAnimation->setEndValue(4);
    this->_widthAnimation->start();
    this->_animClock = true;
}

void BorderRoundedRectungle::StartPressedAnimation()
{
    this->_heightAnimation->setDuration(90);
    if (this->_heightAnimation->state() != QPropertyAnimation::Running)
    {
        this->_heightAnimation->setPropertyName("_heightOFFSET");
    }
    this->_heightAnimation->setStartValue(this->_heightOFFSET);
    this->_heightAnimation->setEndValue(10);
    this->_heightAnimation->start();
}

void BorderRoundedRectungle::SetWidthOFFSET(int value)
{
    this->_widthOFFSET = value;
    update();
}

int BorderRoundedRectungle::GetWidthOFFSET()
{
    return this->_widthOFFSET;
}

void BorderRoundedRectungle::SetHeightOFFSET(int value)
{
    this->_heightOFFSET = value;
    update();
}

int BorderRoundedRectungle::GetHeightOFFSET()
{
    return this->_heightOFFSET;
}

void BorderRoundedRectungle::SetFocused(bool value)
{
    this->_isFocused = value;
    if (value)
    {
        StartPressedAnimation();
        this->SetWidthOFFSET(0);
    }
    else
    {
        StartLeavedAnimation();
        this->SetHeightOFFSET(0);
    }
    update();
}

bool BorderRoundedRectungle::IsFocused()
{
    return this->_isFocused;
}

void BorderRoundedRectungle::SetDrawEnabled(bool value)
{
    this->_needDraw = value;
}

void BorderRoundedRectungle::paintEvent(QPaintEvent *event)
{
    (void)event;
    if (this->_needDraw && !this->_isHiden)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor("#fff"), 0.1));
        painter.setBrush(QColor("#fff"));
        painter.drawRoundedRect(QRectF(0,
                                       this->height() / 2 - this->LEFT_PANEL_HEIGHT_MIN / 2 - this->_heightOFFSET,
                                       4 - this->_widthOFFSET,
                                       this->LEFT_PANEL_HEIGHT_MIN + this->_heightOFFSET * 2),
                                5,
                                5);
        painter.drawRect(QRectF(0,
                                this->height() / 2 - this->LEFT_PANEL_HEIGHT_MIN / 2 - this->_heightOFFSET,
                                2 - this->_widthOFFSET < 0 ? 0 : 2 - this->_widthOFFSET,
                                this->LEFT_PANEL_HEIGHT_MIN + this->_heightOFFSET * 2));
    }
}

// *************************************************************
// Left Border Button class
// *************************************************************

ComputerButton::ComputerButton(QWidget *parent)
    : QWidget(parent)
    , _mainLayout(nullptr)
    , _leftPanel(nullptr)
    , _rightPanel(nullptr)
    , _rightPanelButton(nullptr)
    , _leftPanelRect(nullptr)
    , _computer(nullptr)
    , _stackedIndex(-1)
{
    qDebug() << "[CREATED]" << this;
    this->setFixedSize(QSize(this->WIDTH, this->HEIGHT));
    SetMemory();
    SetupModules();
}

ComputerButton::~ComputerButton()
{
    qDebug() << "[DELETED]" << this;
    if (this->_leftPanelRect != nullptr)
        delete this->_leftPanelRect;
    if (this->_rightPanelButton != nullptr)
        delete this->_rightPanelButton;
    if (this->_rightPanel != nullptr)
        delete this->_rightPanel;
    if (this->_leftPanel != nullptr)
        delete this->_leftPanel;
    if (this->_mainLayout != nullptr)
        delete this->_mainLayout;
}

void ComputerButton::SetMemory()
{
    if (this->_mainLayout == nullptr)
        this->_mainLayout = new QHBoxLayout();
    if (this->_leftPanel == nullptr)
        this->_leftPanel = new QWidget();
    if (this->_rightPanel == nullptr)
        this->_rightPanel = new QWidget();
    if (this->_rightPanelButton == nullptr)
        this->_rightPanelButton = new CenterButton();
    if (this->_leftPanelRect == nullptr)
        this->_leftPanelRect = new BorderRoundedRectungle();
}

void ComputerButton::SetupModules()
{
    this->setLayout(this->_mainLayout);
    this->_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->_mainLayout->setSpacing(0);
    this->_mainLayout->addWidget(this->_leftPanel);
    this->_mainLayout->addWidget(this->_rightPanel);

    this->_leftPanel->setFixedWidth(4);
    this->_leftPanel->setLayout(new QHBoxLayout());
    this->_leftPanel->layout()->setContentsMargins(0, 0, 0, 0);
    this->_leftPanel->layout()->setSpacing(0);
    this->_leftPanel->layout()->addWidget(this->_leftPanelRect);

    this->_rightPanel->setLayout(new QHBoxLayout());
    this->_rightPanel->layout()->setContentsMargins(8, 1, 12, 1);
    this->_rightPanel->layout()->setSpacing(0);
    this->_rightPanel->layout()->addWidget(this->_rightPanelButton);

    this->_leftPanelRect->SetDrawEnabled(false);

    connect(this->_rightPanelButton, &CenterButton::entered, this, &ComputerButton::PanelButtonEntered);
    connect(this->_rightPanelButton, &CenterButton::leaved, this, &ComputerButton::PanelButtonLeaved);
    connect(this->_rightPanelButton, &CenterButton::clicked, this, &ComputerButton::PanelButtonPressed);
}

void ComputerButton::SetFocused(bool value)
{
    if (value)
    {
        this->_leftPanelRect->SetDrawEnabled(true);
    }
    this->_leftPanelRect->SetFocused(value);
    this->_rightPanelButton->SetFocused(value);
}

bool ComputerButton::IsFocused()
{
    return this->_leftPanelRect->IsFocused() && this->_rightPanelButton->IsFocused();
}

void ComputerButton::SetLeftPanelEnabled(bool value)
{
    if (value)
    {
        this->_leftPanelRect->Show();
        this->_rightPanelButton->Pin();
    }
    else
    {
        this->_leftPanelRect->Hide();
        this->_rightPanelButton->UnPin();
    }
}

void ComputerButton::SetImage(QString value)
{
    this->_rightPanelButton->SetImage(value);
}

void ComputerButton::SetComputer(Computer *computer)
{
    this->_computer = computer;
}

Computer* ComputerButton::GetComputer()
{
    return this->_computer;
}

void ComputerButton::SetStackedIndex(int value)
{
    this->_stackedIndex = value;
}

int ComputerButton::GetStackedIndex()
{
    return this->_stackedIndex;
}

void ComputerButton::PanelButtonEntered()
{
    this->_leftPanelRect->SetDrawEnabled(true);
    this->_leftPanelRect->StartEnteredAnimation();
}

void ComputerButton::PanelButtonLeaved()
{
    this->_leftPanelRect->StartLeavedAnimation();
}

void ComputerButton::PanelButtonPressed()
{
    if (!IsFocused())
    {
        this->SetFocused(true);
        emit clicked(this);
    }
}
