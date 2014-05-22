#ifndef DETECTOR_ITEM_H
#define DETECTOR_ITEM_H


#include "ParameterizedItem.h"

class DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit DetectorItem(ParameterizedItem *parent=0);
    ~DetectorItem(){}
};


#endif
