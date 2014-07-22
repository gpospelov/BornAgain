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

QColor suggestMaterialColor(const QString &name);
//MaterialProperty getMaterialProperty(MaterialItem *material);
MaterialProperty getDefaultMaterialProperty();
ColorProperty suggestMaterialColorProperty(const QString &name);

//QString getMaterialName(const MaterialProperty &material_property);
//QColor getMaterialColor(const MaterialProperty &material_property);

IMaterial *createDomainMaterial(const MaterialItem *material);
IMaterial *createDomainMaterial(const QString &name);

}


#endif
