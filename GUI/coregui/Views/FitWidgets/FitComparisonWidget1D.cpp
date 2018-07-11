// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget1D.cpp
//! @brief     Implements class FitComparisonWidget1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitComparisonWidget1D.h"
#include "Data1DViewItem.h"
#include "FitComparisonViewController.h"
#include "FitFlowWidget.h"
#include "FitSuiteItem.h"
#include "IntensityDataPropertyWidget.h"
#include "JobItem.h"
#include "Plot1D.h"
#include "Plot1DCanvas.h"
#include "PlotStatusLabel.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include <QAction>
#include <QGridLayout>
#include <QVBoxLayout>

FitComparisonWidget1D::FitComparisonWidget1D(QWidget* parent)
    : SessionItemWidget(parent)
    , m_data_plot(new Plot1DCanvas)
    , m_diff_plot(new Plot1DCanvas)
    , m_fitFlowWidget(new FitFlowWidget)
    , m_statusLabel(new PlotStatusLabel(nullptr, this))
    , m_propertyWidget(new IntensityDataPropertyWidget)
    , m_resetViewAction(new QAction(this))
    , m_comparisonController(new FitComparison1DViewController(this))
{
    auto vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    auto gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    gridLayout->addWidget(m_data_plot, 0, 0, 1, -1);
    gridLayout->addWidget(m_diff_plot, 1, 0, 1, 2);
    gridLayout->addWidget(m_fitFlowWidget, 1, 2, 1, 1);

    vlayout->addLayout(gridLayout);
    vlayout->addWidget(m_statusLabel);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addLayout(vlayout);
    hlayout->addWidget(m_propertyWidget);
    setLayout(hlayout);

    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, &QAction::triggered, this,
            &FitComparisonWidget1D::onResetViewAction);

    m_propertyWidget->setVisible(false);
}

FitComparisonWidget1D::~FitComparisonWidget1D() = default;

QList<QAction*> FitComparisonWidget1D::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_propertyWidget->actionList();
}

void FitComparisonWidget1D::subscribeToItem()
{
    if (!jobItem()->isValidForFitting())
        return;

    jobItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_STATUS) {
                if (jobItem()->isCompleted())
                    onResetViewAction();
            }
        },
        this);

    m_comparisonController->setItem(jobItem());

    m_data_plot->setItem(viewItem());
    m_diff_plot->setItem(m_comparisonController->diffItemView());
    m_fitFlowWidget->setItem(jobItem()->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addPlot(m_data_plot->plot1D());
    m_statusLabel->addPlot(m_diff_plot->plot1D());

    m_propertyWidget->setItem(viewItem());
}

void FitComparisonWidget1D::unsubscribeFromItem()
{
    if (!currentItem())
        return;

    m_comparisonController->clear();
}

void FitComparisonWidget1D::onResetViewAction()
{
    viewItem()->resetView();
    m_comparisonController->resetDiffView();
}

JobItem* FitComparisonWidget1D::jobItem()
{
    JobItem* jobItem = dynamic_cast<JobItem*>(currentItem());
    return jobItem;
}

Data1DViewItem* FitComparisonWidget1D::viewItem()
{
    auto view_item = dynamic_cast<Data1DViewItem*>(jobItem()->dataItemView());
    Q_ASSERT(view_item);
    return view_item;
}
