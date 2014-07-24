#include "MaterialProperty.h"
#include "MaterialItem.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"

QString MaterialProperty::getName() const
{
    MaterialProperty property(getIdentifier());
    MaterialItem *materialItem = MaterialEditor::getMaterialModel()->getMaterial(property);
    if(materialItem) {
        return materialItem->itemName();
    } else {
        return QString("Undefined");
    }
}


QColor MaterialProperty::getColor() const
{
    MaterialProperty property(getIdentifier());
    MaterialItem *materialItem = MaterialEditor::getMaterialModel()->getMaterial(property);
    if(materialItem) {
        return materialItem->getColor();
    } else {
        return QColor(Qt::red);
    }

}


QPixmap MaterialProperty::getPixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(getColor());
    return pixmap;
}

bool MaterialProperty::isDefined() const
{
    return !m_identifier.isEmpty();
}
