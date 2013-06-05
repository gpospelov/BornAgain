#ifndef OBJECTPROPERTYMANAGER_H
#define OBJECTPROPERTYMANAGER_H

//! collection of classes extending QtPropertyBrowser functionality

#include <QtAbstractPropertyManager>
#include <QtDoublePropertyManager>
#include "Types.h"

class ObjectComplexPropertyManagerPrivate;

//! The ObjectComplexPropertyManager provides and manages complex_t property.
class QT_QTPROPERTYBROWSER_EXPORT ObjectComplexPropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT
public:
    ObjectComplexPropertyManager(QObject *parent = 0);
    ~ObjectComplexPropertyManager();

    QtDoublePropertyManager *subDoublePropertyManager() const;

    //QPointF value(const QtProperty *property) const;
    complex_t value(const QtProperty *property) const;
    int decimals(const QtProperty *property) const;

public Q_SLOTS:
//    void setValue(QtProperty *property, const QPointF &val);
    void setValue(QtProperty *property, const complex_t &val);
    void setDecimals(QtProperty *property, int prec);
Q_SIGNALS:
//    void valueChanged(QtProperty *property, const QPointF &val);
    void valueChanged(QtProperty *property, const complex_t &val);
    void decimalsChanged(QtProperty *property, int prec);
protected:
    QString valueText(const QtProperty *property) const;
    virtual void initializeProperty(QtProperty *property);
    virtual void uninitializeProperty(QtProperty *property);
private:
    ObjectComplexPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ObjectComplexPropertyManager)
    Q_DISABLE_COPY(ObjectComplexPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QtProperty *))
};

#endif // OBJECTPROPERTYMANAGER_H
