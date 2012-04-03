#ifndef ISAMPLE_H
#define ISAMPLE_H

#include "exceptions.h"

class ISample
{
public:
    virtual ~ISample() {}

    virtual void add(ISample* p_child);
//    virtual void remove(ISample* p_child);
//    virtual ISample* getChild(size_t index);
};

void ISample::add(ISample* p_child)
{
    throw NotImplementedException("This sample class is not allowed to have subsamples.");
}

//void ISample::remove(ISample* p_child)
//{
//    throw NotImplementedException("This sample class is not allowed to have subsamples.");
//}

//ISample *ISample::getChild(size_t index)
//{
//    throw NotImplementedException("This sample class is not allowed to have subsamples.");
//}

#endif // ISAMPLE_H
