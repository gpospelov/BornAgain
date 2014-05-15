#ifndef OBJECTVARIANTMANAGER_H
#define OBJECTVARIANTMANAGER_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantPropertyManager>
#include "FormFactorProperty.h"
#include "MaterialProperties.h"
#include "GroupProperty.h"
class QObject;

//! The ObjectVariantManager class provides and manages user defined
//! QVariant based properties.
class PropertyVariantManager : public QtVariantPropertyManager
{
    Q_OBJECT
public:
    PropertyVariantManager(QObject *parent = 0);

    virtual QVariant value(const QtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;
    static int materialTypeId();
    static int formFactorTypeId();
    static int groupTypeId();

public slots:
    virtual void setValue(QtProperty *property, const QVariant &val);
protected:
    virtual QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;

    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    QMap<const QtProperty *, MaterialProperty> theMaterialValues;
    QMap<const QtProperty *, FormFactorProperty> theFormFactorValues;
    QMap<const QtProperty *, GroupProperty> theGroupValues;
};

#endif // OBJECTVARIANTMANAGER_H
