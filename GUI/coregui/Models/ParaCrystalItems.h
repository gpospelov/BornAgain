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



#endif

