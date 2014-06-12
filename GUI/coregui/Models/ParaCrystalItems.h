#ifndef PARACRYSTALITEMS_H
#define PARACRYSTALITEMS_H



#include "ParameterizedGraphicsItem.h"


class InterferenceFunction1DParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_PEAK_DISTANCE, P_DAMPING_LENGTH, P_DOMAIN_SIZE,
                         P_KAPPA, P_PDF;
    explicit InterferenceFunction1DParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunction1DParaCrystalItem(){}
};


class InterferenceFunction2DParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_TYPE, P_ROTATION_ANGLE, P_DAMPING_LENGTH,
                         P_DOMAIN_SIZE1, P_DOMAIN_SIZE2, P_XI_INTEGRATION,
                         P_PDF1, P_PDF2;
    explicit InterferenceFunction2DParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunction2DParaCrystalItem(){}
};


#endif

