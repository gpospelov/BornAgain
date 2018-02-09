// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.cpp
//! @brief     Implements class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobResultsPresenter.h"
#include "FitComparisonWidget.h"
#include "IntensityDataProjectionsWidget.h"
#include "IntensityDataWidget.h"
#include "JobItem.h"
#include "SpecularDataWidget.h"

namespace {
// Will switch to the presentation which was used before for given item
const bool use_job_last_presentation = true;
}

JobResultsPresenter::JobResultsPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::IntensityDataPresentation, create_new<IntensityDataWidget>);

    registerWidget(Constants::IntensityProjectionsPresentation,
                   create_new<IntensityDataProjectionsWidget>);

    registerWidget(Constants::FitComparisonPresentation, create_new<FitComparisonWidget>);

    registerWidget(Constants::SpecularDataPresentation, create_new<SpecularDataWidget>);
}

QString JobResultsPresenter::itemPresentation() const
{
    if (use_job_last_presentation)
        return currentItem()->getItemValue(JobItem::P_PRESENTATION_TYPE).toString();
    else
        return selectedPresentation();
}

void JobResultsPresenter::setPresentation(const QString& presentationType)
{
    ItemComboWidget::setPresentation(presentationType);
    currentItem()->setItemValue(JobItem::P_PRESENTATION_TYPE, presentationType);
}

void JobResultsPresenter::setDefaultPresentation()
{
    auto job_item = dynamic_cast<JobItem*>(currentItem());
    Q_ASSERT(job_item);
    setPresentation(job_item->defaultPresentationType());
}

//! Returns list of presentation types, available for given item. JobItem with fitting abilities
//! is valid for IntensityDataWidget and FitComparisonWidget.

QStringList JobResultsPresenter::activePresentationList(SessionItem* item)
{
    JobItem* jobItem = dynamic_cast<JobItem*>(item);

    QStringList result = presentationList(jobItem);

    if (!jobItem->isValidForFitting())
        result.removeAll(Constants::FitComparisonPresentation);

    return result;
}

QStringList JobResultsPresenter::presentationList(SessionItem* item)
{
    Q_ASSERT(item->modelType() == Constants::JobItemType);

    return QStringList() << Constants::IntensityDataPresentation
                         << Constants::SpecularDataPresentation
                         << Constants::IntensityProjectionsPresentation
                         << Constants::FitComparisonPresentation;
}
