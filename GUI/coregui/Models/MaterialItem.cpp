#include "MaterialItem.h"

QStringList MaterialItem::m_type_names = QStringList()
        << QString("Homogeneous Material")
        << QString("Homogeneous Magnetic Material");

MaterialItem::MaterialItem(const QString &name, MaterialType type)
    : m_name(name)
    , m_type(type)
{

}



