#ifndef INSTRUMENT_ITEM_H
#define INSTRUMENT_ITEM_H


#include "ParameterizedItem.h"

class InstrumentItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit InstrumentItem(ParameterizedItem *parent=0);
    ~InstrumentItem(){}
};



#endif
