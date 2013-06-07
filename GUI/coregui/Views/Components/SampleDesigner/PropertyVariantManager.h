#ifndef OBJECTVARIANTMANAGER_H
#define OBJECTVARIANTMANAGER_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantPropertyManager>
#include "MaterialBrowser.h"
class QObject;

//! The ObjectVariantManager class provides and manages user defined QVariant based properties.
class PropertyVariantManager : public QtVariantPropertyManager
{
    Q_OBJECT
public:
    PropertyVariantManager(QObject *parent = 0);
    ~PropertyVariantManager();

    virtual QVariant value(const QtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;

//    virtual QStringList attributes(int propertyType) const;
//    virtual int attributeType(int propertyType, const QString &attribute) const;
//    virtual QVariant attributeValue(const QtProperty *property, const QString &attribute) const;

    static int materialTypeId();

public slots:
    virtual void setValue(QtProperty *property, const QVariant &val);
//    virtual void setAttribute(QtProperty *property,
//                const QString &attribute, const QVariant &value);
protected:
    virtual QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;

    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
//    struct Data {
//        QString value;
//        QString filter;
//    };
//    QMap<const QtProperty *, Data> theValues;
    QMap<const QtProperty *, MaterialProperty> theValues;
};


#endif // OBJECTVARIANTMANAGER_H
