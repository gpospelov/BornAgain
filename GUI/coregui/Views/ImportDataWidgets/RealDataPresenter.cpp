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
#include "RealDataMaskWidget.h"
#include "IntensityDataWidget.h"
#include "IntensityDataProjectionsWidget.h"
#include "item_constants.h"
#include <QAction>

RealDataPresenter::RealDataPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::IntensityDataPresentation, create_new<IntensityDataWidget>);
    registerWidget(Constants::IntensityProjectionsPresentation, create_new<IntensityDataProjectionsWidget>);
    registerWidget(Constants::MaskEditorPresentation, create_new<RealDataMaskWidget>);
}

QList<QAction*> RealDataPresenter::actionList()
{
    return QList<QAction*>();
}

QStringList RealDataPresenter::activePresentationList(SessionItem*)
{
    return QStringList() << Constants::IntensityDataPresentation
                         << Constants::IntensityProjectionsPresentation
                         << Constants::MaskEditorPresentation;
}
