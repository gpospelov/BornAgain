#ifndef LAYERROUGHNESSITEMS_H
#define LAYERROUGHNESSITEMS_H


#include "ParameterizedItem.h"

class LayerZeroRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_TYPE_NAME;
    explicit LayerZeroRoughnessItem(ParameterizedItem *parent=0);
    ~LayerZeroRoughnessItem(){}
};


class LayerRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_TYPE_NAME, P_SIGMA, P_HURST, P_LATERAL_CORR_LENGTH;
    explicit LayerRoughnessItem(ParameterizedItem *parent=0);
    ~LayerRoughnessItem(){}
};


#endif
