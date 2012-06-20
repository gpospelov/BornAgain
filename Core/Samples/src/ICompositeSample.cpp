#include "ICompositeSample.h"
#include "ICompositeIterator.h"


ICompositeSample::ICompositeSample()
{

}



ICompositeIterator ICompositeSample::createIterator()
{
    return ICompositeIterator(this);
}
