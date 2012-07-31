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
// register child in the container
/* ************************************************************************* */
void ICompositeSample::registerChild(ISample *sample)
{
    if(sample) {
        m_samples.push_back(sample);
    } else {
        std::cout << "ICompositeSample::registerChild() -> Error! Attempt to register NULL child in this " << *this << std::endl;
    }
}


/* ************************************************************************* */
// remove registere child from the container
/* ************************************************************************* */
void ICompositeSample::deregisterChild(ISample *sample)
{
    m_samples.remove(sample);
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
        if(smp) {
            int nlevel = it.get_level();
            for(int i=0; i<nlevel; i++) std::cout << "... ";
            std::cout << (*smp) << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
        it.next();
    }
}


