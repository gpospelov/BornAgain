#include "PythonScriptSampleBuilder.h"

PythonScriptSampleBuilder::PythonScriptSampleBuilder(QDir script_path)
{

}

PythonScriptSampleBuilder::~PythonScriptSampleBuilder()
{
    // release python objects
}

ISample *PythonScriptSampleBuilder::buildSample() const
{
    // use predefined function in python module to create a pyobject
    // which is then 'extracted' to ISample* by boost::python
}
