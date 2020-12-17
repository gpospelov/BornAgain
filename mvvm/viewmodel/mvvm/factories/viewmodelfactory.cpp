//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/factories/viewmodelfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/viewmodel/defaultviewmodel.h"
#include "mvvm/viewmodel/propertyflatviewmodel.h"
#include "mvvm/viewmodel/propertytableviewmodel.h"
#include "mvvm/viewmodel/propertyviewmodel.h"
#include "mvvm/viewmodel/topitemsviewmodel.h"

using namespace ModelView;

std::unique_ptr<ViewModel> Factory::CreateDefaultViewModel(ModelView::SessionModel* model)
{
    return std::make_unique<DefaultViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyViewModel(SessionModel* model)
{
    return std::make_unique<PropertyViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyTableViewModel(SessionModel* model)
{
    return std::make_unique<PropertyTableViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreateTopItemsViewModel(SessionModel* model)
{
    return std::make_unique<TopItemsViewModel>(model);
}

std::unique_ptr<ViewModel> Factory::CreatePropertyFlatViewModel(SessionModel* model)
{
    return std::make_unique<PropertyFlatViewModel>(model);
}
