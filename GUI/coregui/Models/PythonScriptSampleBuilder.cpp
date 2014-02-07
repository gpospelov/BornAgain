#include "PythonScriptSampleBuilder.h"

#include <cstring>
#include <QByteArray>

#include <Python.h>
#include <boost/python.hpp>

namespace bp = boost::python;

const char *PythonScriptSampleBuilder::m_class_name = "PythonSampleBuilder";
const char *PythonScriptSampleBuilder::m_const_function_name = "buildSample";

PythonScriptSampleBuilder::PythonScriptSampleBuilder(QString script_path)
    : m_script_path(script_path)
{
}

PythonScriptSampleBuilder::~PythonScriptSampleBuilder()
{
    // release python objects
}

ISample *PythonScriptSampleBuilder::buildSample() const
{
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance, *pValue;
    Py_Initialize();
    // add path to script:
    QString addPathPython("sys.path.append('");
    addPathPython.append(m_script_path.path());
    addPathPython.append("')");
    QByteArray path_command = addPathPython.toLocal8Bit();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(path_command.data());
    PyRun_SimpleString("sys.path.append('/Users/herck/Development/git/BornAgain/lib')");
    // use predefined function in python module to create a pyobject
    // which is then 'extracted' to ISample* by boost::python
    // build the name object
    QByteArray script_name = m_script_path.completeBaseName().toLocal8Bit();
    pName = PyString_FromString(script_name.data());

    // load the module object
    pModule = PyImport_Import(pName);

    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);

    // get class and instance
    pClass = PyDict_GetItemString(pDict, m_class_name);
    pInstance = PyObject_CallObject(pClass, 0);

    // get the ISample PyObject
    char function_name[12];
    std::strcpy(function_name, m_const_function_name);
    pValue = PyObject_CallMethod(pInstance, function_name, 0);
    ISample *pResult = bp::extract<ISample *>(pValue);

    return pResult;
}
