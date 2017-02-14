// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.cpp
//! @brief     Implements class IntensityDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataCanvas.h"
#include "AppSvc.h"
#include "ColorMap.h"
#include "ColorMapCanvas.h"
#include "IntensityDataItem.h"
#include "SavePlotAssistant.h"
#include "projectmanager.h"
#include <QAction>
#include <QVBoxLayout>
#include <QMouseEvent>

IntensityDataCanvas::IntensityDataCanvas(QWidget *parent)
    : SessionItemWidget(parent)
    , m_colorMap(new ColorMapCanvas(this))
    , m_resetViewAction(nullptr)
    , m_savePlotAction(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_colorMap);
    setLayout(layout);

    m_colorMap->setStatusLabelEnabled(true);

    initActions();

    connect(m_colorMap->customPlot(), SIGNAL(mousePress(QMouseEvent*)),
            this, SLOT(onMousePress(QMouseEvent*)), Qt::UniqueConnection);
}

void IntensityDataCanvas::setItem(SessionItem* item)
{
    IntensityDataItem* intensityItem = dynamic_cast<IntensityDataItem*>(item);
    setIntensityData(intensityItem);
}

QSize IntensityDataCanvas::sizeHint() const
{
    return QSize(500, 400);
}

QSize IntensityDataCanvas::minimumSizeHint() const
{
    return QSize(128, 128);
}

QList<QAction*> IntensityDataCanvas::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_savePlotAction;
}

void IntensityDataCanvas::onResetViewAction()
{
    m_currentItem->resetView();
}

void IntensityDataCanvas::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_colorMap->customPlot(), m_currentItem);
}

void IntensityDataCanvas::onMousePress(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        emit customContextMenuRequested(event->globalPos());
}

void IntensityDataCanvas::setIntensityData(IntensityDataItem* intensityItem)
{
    m_currentItem = intensityItem;
    m_colorMap->setItem(intensityItem);
}

void IntensityDataCanvas::initActions()
{
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SLOT(onResetViewAction()));

    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save");
    m_savePlotAction->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_savePlotAction->setToolTip("Save Plot");
    connect(m_savePlotAction, SIGNAL(triggered()), this, SLOT(onSavePlotAction()));
}
