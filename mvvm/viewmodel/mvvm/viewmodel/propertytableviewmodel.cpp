//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/propertytableviewmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/viewmodel/propertytableviewmodel.h"
#include "mvvm/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

PropertyTableViewModel::PropertyTableViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyTableViewModelController>(model, this), parent)
{
}
