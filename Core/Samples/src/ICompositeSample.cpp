#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "Utils.h"
#include <vector>
#include <sstream>



ICompositeSample::ICompositeSample()
{

}


ICompositeSample::ICompositeSample(const ICompositeSample &other) : ISample(other)
{

}


/* ************************************************************************* */
// create general iterator to walk through the tree of registered composite children
/* ************************************************************************* */
ICompositeIterator ICompositeSample::createIterator()
{
    return ICompositeIterator(this);
}


void ICompositeSample::walk_and_print()
{
    std::cout << getName() << " " << this << std::endl;
    ICompositeIterator it = getCompositeSample()->createIterator();
    it.first();
    while(!it.is_done())
    {
        ISample *smp = it.get_current();
        int nlevel = it.get_level();
        for(int i=0; i<nlevel; i++) std::cout << "... ";
        std::cout << (*smp) << std::endl;
        it.next();
    }
}


