#include "PropertyVariantManager.h"
//#include "DesignerHelper.h"
#include "MaterialBrowser.h"

#include "Types.h"
Q_DECLARE_METATYPE(complex_t)

#include <iostream>

PropertyVariantManager::PropertyVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


PropertyVariantManager::~PropertyVariantManager()
{
}


//int ObjectVariantManager::complexTypeId()
//{
//    return qMetaTypeId<complex_t>();
//}

int PropertyVariantManager::materialTypeId()
{
    return qMetaTypeId<MaterialProperty>();
}


bool PropertyVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int PropertyVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialTypeId())
        return materialTypeId();
//        return QVariant::String;
    return QtVariantPropertyManager::valueType(propertyType);
}

QVariant PropertyVariantManager::value(const QtProperty *property) const
{
    if (theValues.contains(property)) {
        QVariant v;
        v.setValue(theValues[property]);
        std::cout << "PropertyVariantManager::value() -> " << std::endl;
        return v;
    }
    //    return theValues[property].value;
    return QtVariantPropertyManager::value(property);
}

//QStringList ObjectVariantManager::attributes(int propertyType) const
//{
//    if (propertyType == materialTypeId()) {
//        QStringList attr;
//        attr << QLatin1String("filter");
//        return attr;
//    }
//    return QtVariantPropertyManager::attributes(propertyType);
//}

//int ObjectVariantManager::attributeType(int propertyType, const QString &attribute) const
//{
//    if (propertyType == materialTypeId()) {
//        if (attribute == QLatin1String("filter"))
//            return QVariant::String;
//        return 0;
//    }
//    return QtVariantPropertyManager::attributeType(propertyType, attribute);
//}

//QVariant ObjectVariantManager::attributeValue(const QtProperty *property, const QString &attribute) const
//{
//    if (theValues.contains(property)) {
//        if (attribute == QLatin1String("filter"))
//            return theValues[property].filter;
//        return QVariant();
//    }
//    return QtVariantPropertyManager::attributeValue(property, attribute);
//}

QString PropertyVariantManager::valueText(const QtProperty *property) const
{
    if (theValues.contains(property)) {
        return theValues[property].getName();
        //return theValues[property].value;
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon PropertyVariantManager::valueIcon(const QtProperty *property) const
{
    if (theValues.contains(property)) {
        return QIcon(theValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void PropertyVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (theValues.contains(property)) {
//        if (val.type() != QVariant::String && !val.canConvert(QVariant::String))
//            return;
//        QString str = qVariantValue<QString>(val);
//        Data d = theValues[property];
//        if (d.value == str)
//            return;
//        d.value = str;
//        theValues[property] = d;
//        emit propertyChanged(property);
//        emit valueChanged(property, str);
//        return;
        std::cout << "ObjectVariantManager::setValue() -> XXX" << std::endl;

        return;
    }
    QtVariantPropertyManager::setValue(property, val);
}

//void ObjectVariantManager::setAttribute(QtProperty *property,
//                const QString &attribute, const QVariant &val)
//{
//    if (theValues.contains(property)) {
//        if (attribute == QLatin1String("filter")) {
//            if (val.type() != QVariant::String && !val.canConvert(QVariant::String))
//                return;
//            QString str = qVariantValue<QString>(val);
//            Data d = theValues[property];
//            if (d.filter == str)
//                return;
//            d.filter = str;
//            theValues[property] = d;
//            emit attributeChanged(property, attribute, str);
//        }
//        return;
//    }
//    QtVariantPropertyManager::setAttribute(property, attribute, val);
//}

void PropertyVariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == materialTypeId()) {
        std::cout << "ObjectVariantManager::initializeProperty() -> " << std::endl;
        MaterialProperty m;
        theValues[property] = m;
    }
    QtVariantPropertyManager::initializeProperty(property);
}

void PropertyVariantManager::uninitializeProperty(QtProperty *property)
{
    theValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

