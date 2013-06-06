#ifndef OBJECTVARIANTMANAGER_H
#define OBJECTVARIANTMANAGER_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtVariantPropertyManager>
class QObject;

//! The ObjectVariantManager class provides and manages user defined QVariant based properties.
class ObjectVariantManager : public QtVariantPropertyManager
{
    Q_OBJECT
public:
    ObjectVariantManager(QObject *parent = 0);
    ~ObjectVariantManager();

    static int complexTypeId();

    virtual bool isPropertyTypeSupported(int propertyType) const;
    virtual QtVariantProperty *addProperty(int propertyType, const QString &name = QString());

};


#endif // OBJECTVARIANTMANAGER_H
