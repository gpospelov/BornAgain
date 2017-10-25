// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.cpp
//! @brief     Implements class RealDataPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataPresenter.h"
#include "RealDataMaskWidget.h"
#include "item_constants.h"
#include <QAction>

RealDataPresenter::RealDataPresenter(QWidget* parent)
    : ItemComboWidget(parent)
{
    registerWidget(Constants::MaskEditorPresentation, create_new<RealDataMaskWidget>);
}

QList<QAction*> RealDataPresenter::actionList()
{
    return QList<QAction*>();
}

QStringList RealDataPresenter::activePresentationList(SessionItem*)
{
    return QStringList() << Constants::MaskEditorPresentation;
}
