#ifndef LAYERROUGHNESSITEMS_H
#define LAYERROUGHNESSITEMS_H


#include "ParameterizedItem.h"

class BA_CORE_API_ LayerZeroRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit LayerZeroRoughnessItem(ParameterizedItem *parent=0);
    ~LayerZeroRoughnessItem(){}
};


class BA_CORE_API_ LayerBasicRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_SIGMA;
    static const QString P_HURST;
    static const QString P_LATERAL_CORR_LENGTH;
    explicit LayerBasicRoughnessItem(ParameterizedItem *parent=0);
    ~LayerBasicRoughnessItem(){}
};


#endif
