#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "Utils.h"
#include <vector>
#include <sstream>



ICompositeSample::ICompositeSample()
{

}


/* ************************************************************************* */
// create general iterator to walk through the tree of registered composite children
/* ************************************************************************* */
ICompositeIterator ICompositeSample::createIterator()
{
    return ICompositeIterator(this);
}

