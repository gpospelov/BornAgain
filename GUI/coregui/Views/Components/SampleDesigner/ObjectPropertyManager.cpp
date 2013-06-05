#include "ObjectPropertyManager.h"


template <class Value, class PrivateData>
static Value getData(const QMap<const QtProperty *, PrivateData> &propertyMap,
            Value PrivateData::*data,
            const QtProperty *property, const Value &defaultValue = Value())
{
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
        return defaultValue;
    return it.value().*data;
}


template <class Value, class PrivateData>
static Value getValue(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

class ObjectComplexPropertyManagerPrivate
{
    ObjectComplexPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(ObjectComplexPropertyManager)
public:

    struct Data
    {
        Data() : decimals(2) {}
        //QPointF val;
        complex_t val;
        int decimals;
    };

    void slotDoubleChanged(QtProperty *property, double value);
    void slotPropertyDestroyed(QtProperty *property);

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
};

void ObjectComplexPropertyManagerPrivate::slotDoubleChanged(QtProperty *property, double value)
{
    if (QtProperty *prop = m_xToProperty.value(property, 0)) {
//        QPointF p = m_values[prop].val;
//        p.setX(value);
        complex_t p = m_values[prop].val;
        p.real() = value;
        q_ptr->setValue(prop, p);
    } else if (QtProperty *prop = m_yToProperty.value(property, 0)) {
//        QPointF p = m_values[prop].val;
//        p.setY(value);
        complex_t p = m_values[prop].val;
        p.imag() = value;
        q_ptr->setValue(prop, p);
    }
}

void ObjectComplexPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp  = m_xToProperty.value(property, 0)) {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } else if (QtProperty *pointProp = m_yToProperty.value(property, 0)) {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
}


// Creates a manager with the given parent.
ObjectComplexPropertyManager::ObjectComplexPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new ObjectComplexPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotDoubleChanged(QtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

//Destroys this manager, and all the properties it has created.
ObjectComplexPropertyManager::~ObjectComplexPropertyManager()
{
    clear();
    delete d_ptr;
}

// Returns the manager that creates the nested x and y subproperties.
QtDoublePropertyManager *ObjectComplexPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

// Returns the given property's value.
//QPointF ObjectComplexPropertyManager::value(const QtProperty *property) const
complex_t ObjectComplexPropertyManager::value(const QtProperty *property) const
{
//    return getValue<QPointF>(d_ptr->m_values, property);
    return getValue<complex_t>(d_ptr->m_values, property);
}

// Returns the given property's precision, in decimals.
int ObjectComplexPropertyManager::decimals(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &ObjectComplexPropertyManagerPrivate::Data::decimals, property, 0);
}


QString ObjectComplexPropertyManager::valueText(const QtProperty *property) const
{
    const ObjectComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
//    const QPointF v = it.value().val;
    const complex_t v = it.value().val;

    const int dec =  it.value().decimals;
//    return QString(tr("(%1, %2)").arg(QString::number(v.x(), 'f', dec))
//                                 .arg(QString::number(v.y(), 'f', dec)));
    return QString(tr("(%1, %2)").arg(QString::number(v.real(), 'f', dec))
                                 .arg(QString::number(v.imag(), 'f', dec)));
}

// Sets the value of the given property to value. Nested
// properties are updated automatically.
//void ObjectComplexPropertyManager::setValue(QtProperty *property, const QPointF &val)
void ObjectComplexPropertyManager::setValue(QtProperty *property, const complex_t &val)
{
    const ObjectComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;
//    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
//    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.real());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.imag());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

// Sets the precision of the given \a property to \a prec.
void ObjectComplexPropertyManager::setDecimals(QtProperty *property, int prec)
{
    const ObjectComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    ObjectComplexPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

void ObjectComplexPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = ObjectComplexPropertyManagerPrivate::Data();

    QtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

void ObjectComplexPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}


#include "moc_ObjectPropertyManager.cpp"
//#include "ObjectPropertyManager.moc"
