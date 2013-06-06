#include "ObjectVariantManager.h"
//#include "DesignerHelper.h"

#include "Types.h"
Q_DECLARE_METATYPE(complex_t)

#include <iostream>

ObjectVariantManager::ObjectVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


ObjectVariantManager::~ObjectVariantManager()
{
}


int ObjectVariantManager::complexTypeId()
{
    return qMetaTypeId<complex_t>();
}


bool ObjectVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == complexTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


QtVariantProperty *ObjectVariantManager::addProperty(int propertyType, const QString &name)
{
    if (propertyType == complexTypeId()) {
        std::cout << "ObjectVariantManager::addProperty() -> " << std::endl;
        //return 0;
    }
    return QtVariantPropertyManager::addProperty(propertyType, name);
}
