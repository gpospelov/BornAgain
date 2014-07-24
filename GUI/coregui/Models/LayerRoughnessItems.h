#ifndef LAYERROUGHNESSITEMS_H
#define LAYERROUGHNESSITEMS_H


#include "ParameterizedItem.h"

class LayerZeroRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit LayerZeroRoughnessItem(ParameterizedItem *parent=0);
    ~LayerZeroRoughnessItem(){}
};


class LayerBasicRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_SIGMA, P_HURST, P_LATERAL_CORR_LENGTH;
    explicit LayerBasicRoughnessItem(ParameterizedItem *parent=0);
    ~LayerBasicRoughnessItem(){}
};


#endif
