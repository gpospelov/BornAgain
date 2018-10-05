// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.cpp
//! @brief     Implements class RealDataPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataPresenter.h"
#include "GUIHelpers.h"
#include "IntensityDataWidget.h"
#include "IntensityDataProjectionsWidget.h"
#include "item_constants.h"
#include "RealDataItem.h"
#include "RealDataMaskWidget.h"
#include "SpecularDataWidget.h"
#include <cassert>
#include <QAction>

RealDataPresenter::RealDataPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::IntensityDataPresentation, create_new<IntensityDataWidget>);
    registerWidget(Constants::IntensityProjectionsPresentation,
                   create_new<IntensityDataProjectionsWidget>);
    registerWidget(Constants::MaskEditorPresentation, create_new<RealDataMaskWidget>);
    registerWidget(Constants::SpecularDataPresentation, create_new<SpecularDataWidget>);
}

QList<QAction*> RealDataPresenter::actionList()
{
    return QList<QAction*>();
}

QStringList RealDataPresenter::activePresentationList(SessionItem* item)
{
    assert(item && dynamic_cast<RealDataItem*>(item));
    const auto& underlying_data_model = dynamic_cast<RealDataItem*>(item)->underlyingDataModel();

    QStringList result;
    if (underlying_data_model == Constants::IntensityDataType)
        result << Constants::IntensityDataPresentation
               << Constants::IntensityProjectionsPresentation
               << Constants::MaskEditorPresentation;
    else if (underlying_data_model == Constants::SpecularDataType)
        result << Constants::SpecularDataPresentation;
    else
        throw GUIHelpers::Error(
            "Error in RealDataPresenter::activePresentationList: unsupported data type");
    return result;
}
