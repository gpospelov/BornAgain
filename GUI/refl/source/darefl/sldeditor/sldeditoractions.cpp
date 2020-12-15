// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementitem.h>
#include <darefl/sldeditor/sldeditoractions.h>
#include <darefl/sldeditor/sldelementmodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

namespace DaRefl {

struct SLDEditorActions::SLDEditorActionsImpl {
    SLDElementModel* sld_element_model{nullptr};
    SLDEditorActionsImpl() {}
};

SLDEditorActions::SLDEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<SLDEditorActionsImpl>()) {}

void SLDEditorActions::setModel(SLDElementModel* model) {
    p_impl->sld_element_model = model;
}

SLDEditorActions::~SLDEditorActions() = default;

} // namespace DaRefl
