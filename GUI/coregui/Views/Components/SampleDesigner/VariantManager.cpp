#include "VariantManager.h"
#include "DesignerHelper.h"
#include <iostream>

VariantManager::VariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{
    connect(this, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
    connect(this, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

VariantManager::~VariantManager()
{

}

void VariantManager::slotValueChanged(QtProperty *property, const QVariant &value)
{
    if (xToProperty.contains(property)) {
        QtProperty *pointProperty = xToProperty[property];
        QVariant v = this->value(pointProperty);
//        QPointF p = v.value<QPointF>();
//        p.setX(value.value<double>());
//        setValue(pointProperty, p);
        complex_t p = v.value<complex_t>();
        p.real() =  value.value<double>();
        QVariant v2;
        v2.setValue(p);
        setValue(pointProperty, v2);

    } else if (yToProperty.contains(property)) {
        QtProperty *pointProperty = yToProperty[property];
        QVariant v = this->value(pointProperty);
//        QPointF p = v.value<QPointF>();
//        p.setY(value.value<double>());
//        setValue(pointProperty, p);
        complex_t p = v.value<complex_t>();
        p.imag() = value.value<double>();
        QVariant v2;
        v2.setValue(p);
        setValue(pointProperty, v2);
    }
}

void VariantManager::slotPropertyDestroyed(QtProperty *property)
{
    if (xToProperty.contains(property)) {
        QtProperty *pointProperty = xToProperty[property];
        propertyToData[pointProperty].x = 0;
        xToProperty.remove(property);
    } else if (yToProperty.contains(property)) {
        QtProperty *pointProperty = yToProperty[property];
        propertyToData[pointProperty].y = 0;
        yToProperty.remove(property);
    }
}

bool VariantManager::isPropertyTypeSupported(int propertyType) const
{
    std::cout << "VariantManager::isPropertyTypeSupported() -> propertyType:" << propertyType << " " << qMetaTypeId<complex_t>() << std::endl;
//    if (propertyType == QVariant::PointF) {
//        return true;
    if (propertyType == qMetaTypeId<complex_t>()) {
        std::cout << "VariantManager::isPropertyTypeSupported() -> supported!" << std::endl;
        return true;
    }
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int VariantManager::valueType(int propertyType) const
{
    std::cout << "VariantManager::valueType() -> " << std::endl;
//    if (propertyType == QVariant::PointF) {
//        return QVariant::PointF;
    if (propertyType == qMetaTypeId<complex_t>()) {
        std::cout << "VariantManager::valueType() -> XXX " << std::endl;
        return qMetaTypeId<complex_t>();
        //return QVariant::Double;
    }
    return QtVariantPropertyManager::valueType(propertyType);
}

QVariant VariantManager::value(const QtProperty *property) const
{
    if (propertyToData.contains(property))
        return propertyToData[property].value;
    return QtVariantPropertyManager::value(property);
}

QString VariantManager::valueText(const QtProperty *property) const
{
//    if (propertyToData.contains(property)) {
//        QVariant v = propertyToData[property].value;
//        //QPointF p = v.value<QPointF>();
//        complex_t p = v.value<complex_t>();
////        return QString(tr("(%1, %2)").arg(QString::number(p.x()))
////                                 .arg(QString::number(p.y())));
//        return QString(tr("(%1, %2)").arg(QString::number(p.real()))
//                       .arg(QString::number(p.imag())));
//    }
    return QtVariantPropertyManager::valueText(property);
}

void VariantManager::setValue(QtProperty *property, const QVariant &val)
{
//    if (propertyToData.contains(property)) {

//        if (val.type() != qMetaTypeId<complex_t>() && !val.canConvert(qMetaTypeId<complex_t>()))
//            return;
//        //QPointF p = val.value<QPointF>();
//        complex_t p = val.value<complex_t>();

//        Data d = propertyToData[property];
//        d.value.setValue(p);
//        if (d.x)
//            d.x->setValue(p.real());
//        if (d.y)
//            d.y->setValue(p.imag());
//        propertyToData[property] = d;
//        emit propertyChanged(property);
//        emit valueChanged(property, p.real());
//        return;
//    }
    QtVariantPropertyManager::setValue(property, val);
}

void VariantManager::initializeProperty(QtProperty *property)
{
//    if (propertyType(property) == qMetaTypeId<complex_t>()) {
//        Data d;

////        d.value = QPointF(0, 0);
//        d.value.setValue(complex_t(1, 0));

//        VariantManager *that = (VariantManager *)this;

//        d.x = that->addProperty(QVariant::Double);
//        d.x->setPropertyName(tr("real"));
//        property->addSubProperty(d.x);
//        xToProperty[d.x] = property;

//        d.y = that->addProperty(QVariant::Double);
//        d.y->setPropertyName(tr("imag"));
//        property->addSubProperty(d.y);
//        yToProperty[d.y] = property;

//        propertyToData[property] = d;
//    }
    QtVariantPropertyManager::initializeProperty(property);
}

void VariantManager::uninitializeProperty(QtProperty *property)
{
//    if (propertyToData.contains(property)) {
//        Data d = propertyToData[property];
//        if (d.x)
//            xToProperty.remove(d.x);
//        if (d.y)
//            yToProperty.remove(d.y);
//        propertyToData.remove(property);
//    }
    QtVariantPropertyManager::uninitializeProperty(property);
}
