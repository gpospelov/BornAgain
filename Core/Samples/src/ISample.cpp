#include "ISample.h"
#include "ICompositeSample.h"
#include "ICompositeIterator.h"
#include "Utils.h"


ISample::ISample()
{

}


/* ************************************************************************* */
// copy constructor
// we are consciously not copying parameter pool, it should be done in child class
/* ************************************************************************* */
ISample::ISample(const ISample &other) : INamed(other)
{

}


/* ************************************************************************* */
// assignment operator
// we are consciously not copying parameter pool, it should be done in child class
/* ************************************************************************* */
ISample &ISample::operator=(const ISample &other)
{
    if( this != &other)
    {
        INamed::operator=(other);
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


void ISample::init_parameters()
{
    throw NotImplementedException("ISample::init_parameters() -> Error! Method is not implemented");
}


/* ************************************************************************* */
// create new parameter pool which contains all local parameter and  parameters of children
// user have to delete it
/* ************************************************************************* */
ParameterPool *ISample::createParameterTree()
{
    ParameterPool *newpool = new ParameterPool;
    std::string path("/");
    addParametersToExternalPool(path, newpool);
    return newpool;
}


/* ************************************************************************* */
// add parameters from local pool to external pool and call recursion over direct children
/* ************************************************************************* */
void ISample::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number)
{
    // adding trailing slash, if it is not already there
    if( path[path.length()-1] != '/' ) path += "/";

    // constructing new path, using object name and copy number
    std::ostringstream osCopyNumber;
    if(copy_number >=0) osCopyNumber << copy_number;
    path =  path + getName() + osCopyNumber.str() + "/";

    // copy local parameter to external pool
    m_parameters.copyToExternalPool(path, external_pool);

    // going through direct children of given sample and copy they parameters recursively
    ICompositeSample *sample = getCompositeSample();
    if( sample ) {

        // Here we need some default mechanism to handle cases with many children with same name.
        // Lets run through all direct children and save they names
        Utils::StringUsageMap strUsageMap;
        for(ICompositeSample::iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            strUsageMap.add( path +(*it)->getName() ); // saving children name
        }

        // Now we run through direct children again, and assign copy number for all children with same name
        Utils::StringUsageMap strUsageMap2;
        for(ICompositeSample::iterator_t it=sample->begin_shallow(); it!=sample->end_shallow(); ++it) {
            std::string children_name = path +(*it)->getName();
            strUsageMap2.add(children_name);
            int ncopy = strUsageMap2[children_name]-1; // staring from 0

            // if object is in single exemplar, we do not want any copy number
            if(strUsageMap[children_name] == 1) ncopy = -1;

            (*it)->addParametersToExternalPool(path, external_pool, ncopy);
        }

    } // sample

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
