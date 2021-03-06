//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorWidget.cpp
//! @brief     Implements class JobSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/JobWidgets/JobSelectorWidget.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/JobWidgets/JobListWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobPropertiesWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorActions.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorToolBar.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QHBoxLayout>
#include <QSplitter>

JobSelectorWidget::JobSelectorWidget(JobModel* jobModel, QWidget* parent)
    : QWidget(parent)
    , m_jobSelectorActions(new JobSelectorActions(jobModel, this))
    , m_toolBar(new JobSelectorToolBar(m_jobSelectorActions, this))
    , m_jobListWidget(new JobListWidget)
    , m_jobProperties(new JobPropertiesWidget)
    , m_jobModel(nullptr)
{
    setWindowTitle(Constants::JobSelectorWidgetName);
    setObjectName("JobSelectorWidget");

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    setModel(jobModel);

    auto splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(m_jobListWidget);
    splitter->addWidget(m_jobProperties);
    splitter->setChildrenCollapsible(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

    m_jobSelectorActions->setSelectionModel(m_jobListWidget->selectionModel());

    connect(m_jobListWidget, &JobListWidget::contextMenuRequest, m_jobSelectorActions,
            &JobSelectorActions::onContextMenuRequest);
    connect(m_jobListWidget, &JobListWidget::selectionChanged, this,
            &JobSelectorWidget::onSelectionChanged);
}

void JobSelectorWidget::setModel(JobModel* jobModel)
{
    m_jobModel = jobModel;
    m_jobListWidget->setModel(m_jobModel);
}

QSize JobSelectorWidget::sizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth() * 2);
}

QSize JobSelectorWidget::minimumSizeHint() const
{
    return QSize(StyleUtils::PropertyPanelWidth(), StyleUtils::PropertyPanelWidth());
}

const JobItem* JobSelectorWidget::currentJobItem() const
{
    return m_jobListWidget->currentJobItem();
}

void JobSelectorWidget::makeJobItemSelected(JobItem* item)
{
    ASSERT(item);
    m_jobListWidget->makeJobItemSelected(item);
}

void JobSelectorWidget::onSelectionChanged(JobItem* jobItem)
{
    m_jobProperties->setItem(jobItem);
    emit selectionChanged(jobItem);
}
