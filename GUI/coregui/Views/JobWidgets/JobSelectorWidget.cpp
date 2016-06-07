// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobSelectorWidget.cpp
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
#include "JobModel.h"
#include "JobItem.h"
#include "JobPropertiesWidget.h"
#include "JobListWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include "progressbar.h"
#include <QSplitter>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

JobSelectorWidget::JobSelectorWidget(JobModel *model, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobListWidget(new JobListWidget(this))
    , m_jobProperties(new JobPropertiesWidget(this))
{
    setModel(model);

    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Selector"));

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_jobListWidget);
    m_splitter->addWidget(m_jobProperties);
    m_splitter->setChildrenCollapsible(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);
}


void JobSelectorWidget::setModel(JobModel *model)
{
    if(model != m_jobModel) {
        m_jobModel = model;
        m_jobListWidget->setModel(m_jobModel);
        m_jobProperties->setModel(m_jobModel);
    }
}

void JobSelectorWidget::makeJobItemSelected(JobItem *item)
{
    Q_ASSERT(item);
    //qDebug() << "JobSelectorWidget::makeJobItemSelected(NJobItem *item)" << item;
    QModelIndex index = m_jobModel->indexOfItem(item);
    Q_ASSERT(index.isValid());
    m_jobListWidget->makeJobItemSelected(index);
}
