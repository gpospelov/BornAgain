#ifndef MATERIALVARIANTMANAGER_H
#define MATERIALVARIANTMANAGER_H

#include <QtVariantPropertyManager>
#include "RefractiveIndexProperty.h"


class MaterialVariantManager : public QtVariantPropertyManager
{
    Q_OBJECT
public:
    MaterialVariantManager(QObject *parent = 0);

    virtual QVariant value(const QtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;

    static int refractiveIndexTypeId();
//    static int formFactorTypeId();

public slots:
    virtual void setValue(QtProperty *property, const QVariant &val);

protected:
    virtual QString valueText(const QtProperty *property) const;
    QIcon valueIcon(const QtProperty *property) const;

    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
//    QMap<const QtProperty *, MaterialProperty> theMaterialValues;
//    QMap<const QtProperty *, FormFactorProperty> theFormFactorValues;
    QMap<const QtProperty *, RefractiveIndexProperty> m_RefractiveIndexValues;
};


#endif

