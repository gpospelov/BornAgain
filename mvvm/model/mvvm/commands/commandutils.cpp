//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/commands/commandutils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/commands/commandutils.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/serialization/jsonitembackupstrategy.h"
#include "mvvm/serialization/jsonitemcopystrategy.h"

std::unique_ptr<ModelView::ItemBackupStrategy>
ModelView::CreateItemBackupStrategy(const ModelView::SessionModel* model) {
    assert(model);
    return std::make_unique<JsonItemBackupStrategy>(model->factory());
}

std::unique_ptr<ModelView::ItemCopyStrategy>
ModelView::CreateItemCopyStrategy(const ModelView::SessionModel* model) {
    assert(model);
    return std::make_unique<JsonItemCopyStrategy>(model->factory());
}
