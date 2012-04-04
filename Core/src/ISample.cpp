#include "inc/ISample.h"

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
