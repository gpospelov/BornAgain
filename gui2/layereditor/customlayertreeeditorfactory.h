//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/customlayertreeeditorfactory.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H
#define BORNAGAIN_GUI2_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H

#include "darefl_export.h"
#include "mvvm/editors/defaulteditorfactory.h"

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_LAYEREDITOR_CUSTOMLAYERTREEEDITORFACTORY_H
