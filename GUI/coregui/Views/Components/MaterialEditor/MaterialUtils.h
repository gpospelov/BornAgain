#ifndef MATERIALUTILS_H
#define MATERIALUTILS_H

#include <QColor>
#include <QString>
#include "MaterialItem.h"
#include "MaterialProperty.h"

namespace MaterialUtils
{

QColor suggestMaterialColor(const QString &name);
MaterialProperty getMaterialProperty(MaterialItem *material);

MaterialColorProperty suggestMaterialColorProperty(const QString &name);


}


#endif
