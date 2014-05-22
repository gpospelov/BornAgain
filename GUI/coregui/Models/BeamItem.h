#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}
};



#endif

