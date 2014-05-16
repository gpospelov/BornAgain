#ifndef PARACRYSTALITEMS_H
#define PARACRYSTALITEMS_H



#include "ParameterizedGraphicsItem.h"


class InterferenceFunction1DParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    explicit InterferenceFunction1DParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunction1DParaCrystalItem(){}
};


class InterferenceFunction2DParaCrystalItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    explicit InterferenceFunction2DParaCrystalItem(ParameterizedItem *parent=0);
    ~InterferenceFunction2DParaCrystalItem(){}
};


#endif

