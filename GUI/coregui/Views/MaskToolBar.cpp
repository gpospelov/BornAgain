#include "MaskToolBar.h"
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QSplitter>
#include <QListView>
#include <QButtonGroup>
#include <QDebug>



MaskToolBar::MaskToolBar(QWidget *parent)
{
    this->setParent(parent);
    this->setIconSize(QSize(25,25));


    // selection mode
    m_selectionButton = new QToolButton(this);
    m_selectionButton->setIcon(QIcon(":/images/mouseCursor.png"));
    m_selectionButton->setCheckable(true);
    m_selectionButton->setToolTip(QString("Selection Mode"));
    connect(m_selectionButton, SIGNAL(pressed()), this, SLOT(onChangeToSelectionMode()));

    // pan mode
    m_panButton = new QToolButton(this);
    m_panButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_hand.png"));
    m_panButton->setCheckable(true);
    m_panButton->setToolTip(QString("Pan Mode"));
    connect(m_panButton, SIGNAL(toggled(bool)), this, SLOT(onPanMode(bool)));

    // rectangle
    m_rectangleButton = new QToolButton(this);
    m_rectangleButton->setIcon(QIcon(":/images/rectangle.png"));
    m_rectangleButton->setCheckable(true);
    m_rectangleButton->setToolTip(QString("Create rectangles and squares"));
    connect(m_rectangleButton, SIGNAL(pressed()), this, SLOT(onRectangleButtonPressed()));

    // ellipse
    m_ellipseButton = new QToolButton(this);
    m_ellipseButton->setCheckable(true);
    m_ellipseButton->setToolTip(QString("Create ellipses and circles"));
    m_ellipseButton->setIcon(QIcon(":/images/ellipse.png"));
    connect(m_ellipseButton, SIGNAL(pressed()), this, SLOT(onEllipseButtonPressed()));

    // polygon

    m_polygonButton = new QToolButton(this);
    m_polygonButton->setCheckable(true);
    m_polygonButton->setToolTip(QString("Create Polygons"));
    m_polygonButton->setIcon(QIcon(":/images/polygon.png"));
    connect(m_polygonButton, SIGNAL(pressed()), this, SLOT(onPolygonButtonPressed()));

    // bring to front
    m_bringToFrontButton = new QToolButton(this);
    m_bringToFrontButton->setToolTip(QString("Bring selected item to the front"));
    m_bringToFrontButton->setIcon(QIcon(":/images/bringToFront.png"));
    connect(m_bringToFrontButton, SIGNAL(clicked()), this, SLOT(onBringToFrontClicked()));

    // send to back
    m_sendToBackButton = new QToolButton(this);
    m_sendToBackButton->setToolTip(QString("Send selected item to the back"));
    m_sendToBackButton->setIcon(QIcon(":/images/sendToBack.png"));
    connect(m_sendToBackButton, SIGNAL(clicked()), this, SLOT(onSendToBackClicked()));

    // include
    m_includeButton = new QToolButton(this);
    m_includeButton->setCheckable(true);
    m_includeButton->setToolTip(QString("Including area"));
    m_includeButton->setIcon(QIcon(":/images/include.png"));
    connect(m_includeButton, SIGNAL(clicked()), this, SLOT(onIncludeClicked()));

    // exclude
    m_excludeButton = new QToolButton(this);
    m_excludeButton->setCheckable(true);
    m_excludeButton->setToolTip(QString("Excluding area"));
    m_excludeButton->setIcon(QIcon(":/images/exclude.png"));
    connect(m_excludeButton, SIGNAL(clicked()), this, SLOT(onExcludeClicked()));

    QButtonGroup *drawingGroup = new QButtonGroup(this);
    drawingGroup->addButton(m_rectangleButton);
    drawingGroup->addButton(m_ellipseButton);
    drawingGroup->addButton(m_polygonButton);
    drawingGroup->addButton(m_panButton);
    drawingGroup->addButton(m_selectionButton);

    QButtonGroup *ColorGroup = new QButtonGroup(this);
    ColorGroup->addButton(m_includeButton);
    ColorGroup->addButton(m_excludeButton);


    this->addWidget(m_selectionButton);
    this->addWidget(m_panButton);
    this->addSeparator();
    this->addWidget(m_rectangleButton);
    this->addWidget(m_ellipseButton);
    this->addWidget(m_polygonButton);
    this->addSeparator();
    this->addWidget(m_includeButton);
    this->addWidget(m_excludeButton);
    this->addSeparator();
    this->addWidget(m_bringToFrontButton);
    this->addWidget(m_sendToBackButton);


}

void MaskToolBar::onChangeToSelectionMode()
{
    emit changeToSelectionMode();
}

void MaskToolBar::selectSelectionMode()
{
    m_selectionButton->click();
}

void MaskToolBar::onPanMode(bool isActive)
{
    emit panMode(isActive);
}

void MaskToolBar::onRectangleButtonPressed()
{
    emit rectangleButtonPressed();
}

void MaskToolBar::onEllipseButtonPressed()
{
    emit ellipseButtonPressed();
}

void MaskToolBar::onPolygonButtonPressed()
{
    emit polygonButtonPressed();
}

void MaskToolBar::onBringToFrontClicked()
{
    emit bringToFrontClicked();
}

void MaskToolBar::onSendToBackClicked()
{
    emit sendToBackClicked();
}

void MaskToolBar::onIncludeClicked()
{
    emit includeClicked();
}

void MaskToolBar::onExcludeClicked()
{
    emit excludeClicked();
}
