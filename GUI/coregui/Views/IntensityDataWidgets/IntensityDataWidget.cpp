// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidget.h"
#include "ColorMapCanvas.h"
#include "IntensityDataItem.h"
#include "SavePlotAssistant.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include <QVBoxLayout>
#include <QAction>

IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_colorMap(new ColorMapCanvas(this))
    , m_resetViewAction(0)
    , m_savePlotAction(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_colorMap);
    setLayout(layout);

    m_colorMap->setStatusLabelEnabled(true);

    initActions();
}

void IntensityDataWidget::setItem(SessionItem *item)
{
    IntensityDataItem *intensityItem = dynamic_cast<IntensityDataItem *>(item);
    Q_ASSERT(intensityItem);
    setIntensityData(intensityItem);
}

void IntensityDataWidget::setIntensityData(IntensityDataItem *intensityItem)
{
    m_currentItem = intensityItem;
    m_colorMap->setItem(intensityItem);
}

QList<QAction *> IntensityDataWidget::actionList()
{
    return QList<QAction *>() << m_resetViewAction << m_savePlotAction;
}

void IntensityDataWidget::onResetViewAction()
{
    m_currentItem->resetView();
}

void IntensityDataWidget::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_colorMap->customPlot(), m_currentItem);
}

void IntensityDataWidget::initActions()
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

