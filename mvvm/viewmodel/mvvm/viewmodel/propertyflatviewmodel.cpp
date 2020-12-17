//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/propertyflatviewmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/viewmodel/propertyflatviewmodel.h"
#include "mvvm/viewmodel/standardviewmodelcontrollers.h"

using namespace ModelView;

PropertyFlatViewModel::PropertyFlatViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<PropertyFlatViewModelController>(model, this), parent) {}
