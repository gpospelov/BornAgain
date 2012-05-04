#include "ISample.h"


void ISample::add(ISample* p_child)
{
    (void)p_child;
    throw NotImplementedException("This sample class is not allowed to have subsamples.");
}
