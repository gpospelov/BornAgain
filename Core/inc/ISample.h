#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "Exceptions.h"

class ISample
{
public:
    virtual ~ISample() {}

    virtual void add(ISample* p_child);
//    virtual void remove(ISample* p_child);
//    virtual ISample* getChild(size_t index);
};

#endif // ISAMPLE_H
