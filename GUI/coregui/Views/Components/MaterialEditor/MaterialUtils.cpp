#include "MaterialUtils.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include <QDebug>


QColor MaterialUtils::suggestMaterialColor(const QString &name)
{
    if(name == QStringLiteral("Air") ) {
        return QColor(176, 226, 255);
    } else if(name == QStringLiteral("Substrate") ) {
        return QColor(205,102,0);
    } else if ( name == QStringLiteral("Default") ) {
        return QColor(Qt::green);
    }
    return DesignerHelper::getRandomColor();
}


MaterialProperty MaterialUtils::getMaterialProperty(MaterialItem *material)
{
    if(material->getType() == MaterialItem::SubItem)
        throw GUIHelpers::Error("MaterialUtils::getMaterialProperty() -> Error! It's a SubItem, not material.");

    QVariant v = material->property(MaterialProperties::Color);
    MaterialColorProperty colorProperty = v.value<MaterialColorProperty>();
    return MaterialProperty(material->getName(), colorProperty.getColor());
}


MaterialColorProperty MaterialUtils::suggestMaterialColorProperty(const QString &name)
{
    return MaterialColorProperty(MaterialUtils::suggestMaterialColor(name));
}
