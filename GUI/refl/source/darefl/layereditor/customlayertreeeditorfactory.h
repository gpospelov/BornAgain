// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H
#define DAREFL_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H

#include <darefl/darefl_export.h>
#include <mvvm/editors/defaulteditorfactory.h>

namespace DaRefl {

class ApplicationModels;

//! Custom editor factory for LayerTreeView. Substitutes default ExternalProperty editor
//! with custom one, which will offer the choice between all defined materials.

class DAREFLCORE_EXPORT CustomLayerTreeEditorFactory : public ModelView::DefaultEditorFactory {
public:
    CustomLayerTreeEditorFactory(ApplicationModels* models);
    ~CustomLayerTreeEditorFactory();

    std::unique_ptr<ModelView::CustomEditor> createEditor(const QModelIndex& index) const;

private:
    ApplicationModels* m_models;
};

} // namespace DaRefl

#endif // DAREFL_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H
