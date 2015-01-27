// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/MaterialEditor/MaterialUtils.h
//! @brief     Defines class MaterialUtils
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALUTILS_H
#define MATERIALUTILS_H

#include <QColor>
#include <QString>
#include "MaterialProperty.h"
#include "MaterialItem.h"
#include "ColorProperty.h"

class IMaterial;

namespace MaterialUtils
{

BA_CORE_API_ QColor suggestMaterialColor(const QString &name);
BA_CORE_API_ MaterialProperty getDefaultMaterialProperty();
BA_CORE_API_ ColorProperty suggestMaterialColorProperty(const QString &name);
BA_CORE_API_ IMaterial *createDomainMaterial(const MaterialProperty &material_property);

}


#endif
