// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h
//! @brief     Defines class MaterialItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALITEMUTILS_H
#define MATERIALITEMUTILS_H

#include "ColorProperty.h"
#include "MaterialItem.h"
#include "MaterialProperty.h"
#include <QColor>
#include <QString>
#include <memory>

class Material;

namespace MaterialItemUtils
{

BA_CORE_API_ QColor suggestMaterialColor(const QString &name);
BA_CORE_API_ MaterialProperty defaultMaterialProperty();
BA_CORE_API_ ColorProperty suggestMaterialColorProperty(const QString &name);
BA_CORE_API_ std::unique_ptr<Material> createDomainMaterial(
        const MaterialProperty &material_property);

BA_CORE_API_ QString materialTag(const SessionItem &item);

//! Constructs material property corresponding to given material.
BA_CORE_API_ MaterialProperty materialProperty(const SessionItem& materialItem);

//! Calls material selector dialog.
BA_CORE_API_ MaterialProperty selectMaterialProperty(const MaterialProperty &previousMaterial=MaterialProperty());

}


#endif // MATERIALITEMUTILS_H
