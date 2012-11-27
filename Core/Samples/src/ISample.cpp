#include "ISample.h"
#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "Utils.h"

ISample::ISample()
{
}

/* ************************************************************************* */
// default copy constructor
/* ************************************************************************* */
ISample::ISample(const ISample &other) : IParameterized(other)
{
}

/* ************************************************************************* */
// default assignment operator
/* ************************************************************************* */
ISample &ISample::operator=(const ISample &other)
{
    if( this != &other)
    {
        IParameterized::operator=(other);
    }
    return *this;
}

ISample::~ISample()
{
}

ISample *ISample::clone() const
{
    throw NotImplementedException("ISample::clone() -> Error! Method is not implemented");
}

void ISample::print_structure()
{
    std::cout << getName() << " " << this << std::endl;
    if(getCompositeSample()) {
        ICompositeIterator it = getCompositeSample()->createIterator();
        it.first();
        while(!it.is_done())
        {
            ISample *smp = it.get_current();
            if(smp) {
                int nlevel = (int)it.get_level();
                for(int i=0; i<nlevel; i++) std::cout << "... ";
                std::cout << (*smp) << std::endl;
            } else {
                std::cout << "NULL" << std::endl;
            }
            it.next();
        }
    }
}

/* ************************************************************************* */
// add parameters from local pool to external pool and call recursion over direct children
/* ************************************************************************* */
std::string ISample::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number) const
{
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // going through direct children of given sample and copy they parameters recursively
    const ICompositeSample *sample = getCompositeSample();
    if( sample ) {

        // Here we need some default mechanism to handle cases with many children with same name.
        // Lets run through all direct children and save their names
        Utils::StringUsageMap strUsageMap;
        for(ICompositeSample::const_iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            strUsageMap.add( new_path +(*it)->getName() ); // saving children name
        }

        // Now we run through direct children again, and assign copy number for all children with same name
        Utils::StringUsageMap strUsageMap2;
        for(ICompositeSample::const_iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            std::string children_name = new_path +(*it)->getName();
            strUsageMap2.add(children_name);
            int ncopy = strUsageMap2[children_name]-1; // staring from 0

            // if object is in single exemplar, we do not want any copy number
            if(strUsageMap[children_name] == 1) ncopy = -1;

            (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
        }
    }
    return new_path;
}

/* ************************************************************************* */
// same as above
// return new parameter pool which contains all local parameter as well as all
// parameters from CompositeSample; tree user has to take to delete it
//
// example shows how to walk through all subsamples using iterators instead
// of recursion
/* ************************************************************************* */
//ParameterPool *ISample::createParameterTreeTest()
//{
//    // cloning first local parameter pool
//    ParameterPool *newpool = m_parameters.cloneWithPrefix( std::string("/")+getName()+std::string("/"));

//    // walking through children tree
//    ICompositeSample *sample = getCompositeSample();
//    if( sample ) {
//        // using helper to get unique path in the tree as parameter names
//        Utils::StringSampleHelper strHelper;
//        strHelper.add(getName(), 0); // "folder" name, level of nesting (0 - for top level)

//        // loop over children tree
//        ICompositeIterator it = sample->createIterator();
//        it.first();
//        while(!it.is_done())
//        {
//            // adding child name to the path
//            strHelper.add(it.get_current()->getName(), it.get_level() );

//            // access to the poll parameter of child
//            ParameterPool *pool = it.get_current()->getParameterPool();
//            if(pool->size()) {
//                for(ParameterPool::iterator_t ip=pool->begin(); ip!=pool->end(); ip++) {
//                    //std::cout << (*ip).first << " " << (*ip).second << std::endl;
//                    // adding parameter name to the path
//                    strHelper.add( (*ip).first, it.get_level()+1 );
//                    // registering new parameter with full path
//                    newpool->addParameter(strHelper.get_path(), (*ip).second);
//                }
//            }
//            it.next();
//        }
//        //std::cout << *newpool;
//    }
//    return newpool;
//    return 0;
//}
