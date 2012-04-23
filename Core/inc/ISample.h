#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "Exceptions.h"

class ISample
{
public:
    ISample(){}
    virtual ~ISample() {}

    virtual void add(ISample* p_child);
};

#endif // ISAMPLE_H
