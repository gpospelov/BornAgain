#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "Exceptions.h"

class ISample
{
public:
    ISample(){}
    virtual ~ISample() {}

    virtual void add(ISample* p_child);

    virtual ISample *clone() const =0;

//    virtual void remove(ISample* p_child);
//    virtual ISample* getChild(size_t index);
};

#endif // ISAMPLE_H
