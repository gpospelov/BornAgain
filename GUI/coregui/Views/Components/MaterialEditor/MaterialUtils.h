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
