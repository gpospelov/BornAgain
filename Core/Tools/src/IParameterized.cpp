#include "IParameterized.h"
#include "Utils.h"

IParameterized::IParameterized()
{
}

/* ************************************************************************* */
// copy constructor
// we are consciously not copying parameter pool, it should be done in derived class
/* ************************************************************************* */
IParameterized::IParameterized(const IParameterized &other) : INamed(other)
{
}

/* ************************************************************************* */
// assignment operator
// we are consciously not copying parameter pool, it should be done in derived class
/* ************************************************************************* */
IParameterized &IParameterized::operator=(const IParameterized &other)
{
    if( this != &other)
    {
        INamed::operator=(other);
    }
    return *this;
}

/* ************************************************************************* */
// create new parameter pool which contains all local parameter and  parameters of children
// user have to delete it
/* ************************************************************************* */
ParameterPool *IParameterized::createParameterTree() const
{
    ParameterPool *newpool = new ParameterPool;
    std::string path("/");
    addParametersToExternalPool(path, newpool);
    return newpool;
}


/* ************************************************************************* */
// add parameters from local pool to external pool
/* ************************************************************************* */
std::string IParameterized::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number) const
{
    // adding trailing slash, if it is not already there
    if( path[path.length()-1] != '/' ) path += "/";

    // constructing new path, using object name and copy number
    std::ostringstream osCopyNumber;
    if(copy_number >=0) osCopyNumber << copy_number;
    path =  path + getName() + osCopyNumber.str() + "/";

    // copy local parameter to external pool
    m_parameters.copyToExternalPool(path, external_pool);

    return path;
}

/* ************************************************************************* */
// No pure virtual function here, due to problems in exporting abstract classes to python
/* ************************************************************************* */
void IParameterized::init_parameters()
{
    throw NotImplementedException("IParameterized::init_parameters() -> Error! Method is not implemented");
}
