// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobOutputDataWidget.cpp
//! @brief     Implements class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobOutputDataWidget.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobResultsPresenter.h"
#include "JobViewFlags.h"
#include "mainwindow_constants.h"
#include <QVBoxLayout>

namespace {
const bool reuse_widget = true;
}

JobOutputDataWidget::JobOutputDataWidget(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_stackedWidget(new ItemStackPresenter<JobResultsPresenter>(reuse_widget))
{
    setWindowTitle(QLatin1String("Job OutputData"));

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stackedWidget);

    m_stackedWidget->setMinimumSize(600, 600);
    m_stackedWidget->setModel(jobModel);

    setLayout(mainLayout);
}

void JobOutputDataWidget::setItem(JobItem * jobItem)
{
    if(!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    m_stackedWidget->setItem(jobItem);
}

void JobOutputDataWidget::onActivityChanged(int activity)
{
    if(auto widget = m_stackedWidget->currentWidget()) {
        if(activity == JobViewFlags::FITTING_ACTIVITY) {
            widget->setPresentation(Constants::FitComparisonPresentation);
        } else if(activity == JobViewFlags::REAL_TIME_ACTIVITY) {
            widget->setPresentation(Constants::IntensityDataPresentation);
        } else if(activity == JobViewFlags::JOB_VIEW_ACTIVITY) {
            widget->setPresentation(Constants::IntensityDataPresentation);
        }
    }
}

bool JobOutputDataWidget::isValidJobItem(JobItem *item)
{
    if(!item) return false;
    if(item->isCompleted() || item->isCanceled() || item->isFailed()) return true;
    return false;
}
