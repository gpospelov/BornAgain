//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldeditoractions.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/sldeditoractions.h"
#include "gui2/sldeditor/layerelementitem.h"
#include "gui2/sldeditor/sldelementmodel.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/viewmodel/viewmodel.h"

using namespace ModelView;

namespace gui2 {

struct SLDEditorActions::SLDEditorActionsImpl {
    SLDElementModel* sld_element_model{nullptr};
    SLDEditorActionsImpl() {}
};

SLDEditorActions::SLDEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<SLDEditorActionsImpl>())
{
}

void SLDEditorActions::setModel(SLDElementModel* model)
{
    p_impl->sld_element_model = model;
}

SLDEditorActions::~SLDEditorActions() = default;

} // namespace gui2
