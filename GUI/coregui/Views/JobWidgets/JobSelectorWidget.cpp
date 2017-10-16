// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorWidget.cpp
//! @brief     Implements class JobSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobSelectorWidget.h"
#include "JobItem.h"
#include "JobListWidget.h"
#include "JobModel.h"
#include "JobPropertiesWidget.h"
#include "JobSelectorToolBar.h"
#include "JobSelectorActions.h"
#include "StyledToolBar.h"
#include "mainwindow_constants.h"
#include "minisplitter.h"
#include <QHBoxLayout>

JobSelectorWidget::JobSelectorWidget(JobModel* jobModel, QWidget* parent)
    : QWidget(parent)
    , m_splitter(new Manhattan::MiniSplitter)
    , m_jobSelectorActions(new JobSelectorActions(jobModel, this))
    , m_toolBar(new JobSelectorToolBar(m_jobSelectorActions, this))
    , m_jobListWidget(new JobListWidget)
    , m_jobProperties(new JobPropertiesWidget)
    , m_jobModel(nullptr)
{
    setModel(jobModel);

    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle(Constants::JobSelectorWidgetName);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_toolBar);
    m_splitter->addWidget(m_jobListWidget);
    m_splitter->addWidget(m_jobProperties);
    m_splitter->setChildrenCollapsible(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);

    m_jobSelectorActions->setSelectionModel(m_jobListWidget->selectionModel());

    connect(m_jobListWidget, &JobListWidget::contextMenuRequest,
            m_jobSelectorActions, &JobSelectorActions::onContextMenuRequest);
    connect(m_jobListWidget, &JobListWidget::selectionChanged, this,
            &JobSelectorWidget::onSelectionChanged);
}

void JobSelectorWidget::setModel(JobModel* jobModel)
{
    m_jobModel = jobModel;
    m_jobListWidget->setModel(m_jobModel);
}

const JobItem* JobSelectorWidget::currentJobItem() const
{
    return m_jobListWidget->currentJobItem();
}

void JobSelectorWidget::makeJobItemSelected(JobItem* item)
{
    Q_ASSERT(item);
    m_jobListWidget->makeJobItemSelected(item);
}

void JobSelectorWidget::onSelectionChanged(JobItem* jobItem)
{
    m_jobProperties->setItem(jobItem);
    emit selectionChanged(jobItem);
}
