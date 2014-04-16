#ifndef REFRACTIVEINDEXPROPERTY_H
#define REFRACTIVEINDEXPROPERTY_H

#include <QObject>
#include <QMetaType>

class RefractiveIndexProperty
{
public:
    RefractiveIndexProperty() : m_delta(0), m_beta(0) {}

private:
    double m_delta;
    double m_beta;
};

Q_DECLARE_METATYPE(RefractiveIndexProperty)


#endif
