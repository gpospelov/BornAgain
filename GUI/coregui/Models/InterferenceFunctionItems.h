#ifndef PARACRYSTALITEMS_H
#define PARACRYSTALITEMS_H

#include "ParameterizedGraphicsItem.h"


class BA_CORE_API_ InterferenceFunctionRadialParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_PEAK_DISTANCE;
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE;
    static const QString P_KAPPA;
    static const QString P_PDF;
    explicit InterferenceFunctionRadialParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunctionRadialParaCrystalItem(){}
};


class BA_CORE_API_ InterferenceFunction2DParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_TYPE;
    static const QString P_ROTATION_ANGLE;
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE1;
    static const QString P_DOMAIN_SIZE2;
    static const QString P_XI_INTEGRATION;
    static const QString P_PDF1;
    static const QString P_PDF2;
    explicit InterferenceFunction2DParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunction2DParaCrystalItem(){}
    void onPropertyChange(const QString &name);
};


class BA_CORE_API_ InterferenceFunction2DLatticeItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_TYPE;
    static const QString P_ROTATION_ANGLE;
    static const QString P_PDF;
    explicit InterferenceFunction2DLatticeItem(ParameterizedItem *parent=0);
    ~InterferenceFunction2DLatticeItem(){}
};

#endif
