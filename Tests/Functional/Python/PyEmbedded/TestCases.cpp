// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/TestCases.cpp
//! @brief     Implements TestCases class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestCases.h"
#include "PyEmbeddedUtils.h"
#include "BornAgainNamespace.h"
#include "BAVersion.h"
#include "BABuild.h"
#include "SysUtils.h"
#include <iostream>
#include <sstream>

//! Accessing to the information about Python used during the build, content of path.sys variable.

bool SysPath::runTest()
{
    // Python build info
    std::cout << "pythonExecutable():" << BABuild::pythonExecutable() << std::endl;
    std::cout << "pythonVersionString():" << BABuild::pythonVersionString() << std::endl;
    std::cout << "pythonLibraries():" << BABuild::pythonLibraries() << std::endl;
    std::cout << "pythonIncludeDirs():" << BABuild::pythonIncludeDirs() << std::endl;
    std::cout << "pythonLibsVersionString():" << BABuild::pythonLibsVersionString() << std::endl;
    std::cout << "numpyIncludeDir():" << BABuild::numpyIncludeDir() << std::endl;
    std::cout << "numpyVersionString():" << BABuild::numpyVersionString() << std::endl;

    // BornAgain build
    std::cout << "buildLibDir(): " << BABuild::buildLibDir() << std::endl;

    // Runtime environment
    std::cout << "PYTHONPATH: " << SysUtils::getenv("PYTHONPATH") << std::endl;
    std::cout << "PYTHONHOME: " << SysUtils::getenv("PYTHONHOME") << std::endl;

    Py_Initialize();

    // Runtime Python's sys.path
    PyObject *sysPath = PySys_GetObject((char*)"path");
    auto content = PyEmbeddedUtils::toVectorString(sysPath);
    for (auto s : content)
        std::cout << s << std::endl;

    Py_Finalize();

    return !content.empty();
}

//! Importing numpy and accessing its version string.

bool ImportNumpy::runTest()
{
    Py_Initialize();

    PyObject *pmod = PyImport_ImportModule("numpy");
    if (!pmod)
        throw std::runtime_error("Can't load numpy");

    PyObject* pvar = PyObject_GetAttrString(pmod, "__version__");
    Py_DECREF(pmod);
    if (!pvar)
        throw std::runtime_error("Can't get a variable");

    auto version_string = PyEmbeddedUtils::toString(pvar);
    std::cout << "numpy_version_string=" << version_string << std::endl;

    Py_Finalize();

    return !version_string.empty();
}

//! Comparing results of GetVersionNumber() function obtained in "embedded" and "native C++" ways.

bool FunctionCall::runTest()
{

    throw std::runtime_error("XXX");

    Py_Initialize();

    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject *pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load module");

    PyObject* pfun = PyObject_GetAttrString(pmod, "GetVersionNumber");
    Py_DECREF(pmod);
    if (!pfun)
        throw std::runtime_error("Can't get a function");

    PyObject* pargs = Py_BuildValue("()");
    if (!pargs) {
        Py_DECREF(pfun);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* result  = PyEval_CallObject(pfun, pargs);
    Py_DECREF(pfun);
    Py_DECREF(pargs);
    if(!result)
        throw std::runtime_error("Error while calling function");

    auto str = PyEmbeddedUtils::toString(result);

    Py_Finalize();

    return str == BornAgain::GetVersionNumber();
}

//! Creating instance of FormFactorCylinder and calling its method in embedded Python.

bool MethodCall::runTest()
{
    const double radius(5.0), height(6.0);
    Py_Initialize();

    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyList_Append(sysPath, PyString_FromString(BABuild::buildLibDir().c_str()));

    PyObject *pmod = PyImport_ImportModule("bornagain");
    if (!pmod)
        throw std::runtime_error("Can't load module");

    PyObject* pclass = PyObject_GetAttrString(pmod, "FormFactorCylinder");
    Py_DECREF(pmod);
    if (!pclass)
        throw std::runtime_error("Can't get a class");

    PyObject* pargs = Py_BuildValue("(dd)", radius, height);
    if (!pargs) {
        Py_DECREF(pclass);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* pinst  = PyEval_CallObject(pclass, pargs);
    Py_DECREF(pclass);
    Py_DECREF(pargs);

    if(!pinst)
        throw std::runtime_error("Error while creating object");

    // result of FormFactorCylinder
    PyObject* pmeth  = PyObject_GetAttrString(pinst, "getHeight");
    Py_DECREF(pinst);
    if (!pmeth)
        throw std::runtime_error("Can't fetch FormFactorCylinder.getHeight");

    PyObject* pargs2 = Py_BuildValue("()");
    if (!pargs2) {
        Py_DECREF(pmeth);
        throw std::runtime_error("Can't build arguments list");
    }

    PyObject* pres = PyEval_CallObject(pmeth, pargs2);
    Py_DECREF(pmeth);
    Py_DECREF(pargs);

    if (!pres)
        throw std::runtime_error("Error calling FormFactorCylinder.getHeight()");

    double value(0);
    if (!PyArg_Parse(pres, "d", &value))
       throw std::runtime_error("Can't convert class method result");

    Py_DECREF(pres);

    Py_Finalize();

    return value == height;
}

//! From https://www.awasu.com/weblog/embedding-python/calling-python-code-from-your-program/

bool CompiledFunction::runTest()
{
    Py_Initialize();

    // compile our function
    std::stringstream buf ;
    buf << "def add( n1 , n2 ) :" << std::endl
        << "    return n1+n2" << std::endl ;

    PyObject* pCompiledFn = Py_CompileString( buf.str().c_str() , "" , Py_file_input ) ;
    if (!pCompiledFn)
        throw std::runtime_error("Can't compile a function");

    // create a module
    PyObject* pModule = PyImport_ExecCodeModule( "test" , pCompiledFn ) ;
    if (!pModule)
        throw std::runtime_error("Can't exec module");

    // locate the "add" function (it's an attribute of the module)
    PyObject* pAddFn = PyObject_GetAttrString( pModule , "add" ) ;
    if (!pAddFn)
        throw std::runtime_error("Can't locate compiled functione");

    // clean up
    Py_DecRef( pAddFn ) ;
    Py_DecRef( pModule ) ;
    Py_DecRef( pCompiledFn ) ;

    // ------------------------
    // using compiled function
    // ------------------------

    // create a new tuple with 2 elements
    PyObject* pPosArgs = PyTuple_New( 2 ) ;

    PyObject* pVal1 = PyInt_FromLong( 10) ;
    if (!pVal1)
        throw std::runtime_error("Can't create PyInt");
    int rc = PyTuple_SetItem( pPosArgs , 0 , pVal1 ) ; // nb: tuple position 0
    if (rc!=0)
        throw std::runtime_error("Can't add to tuple");

    PyObject* pVal2 = PyInt_FromLong( 20) ;
    if (!pVal2)
        throw std::runtime_error("Can't create PyInt");
    rc = PyTuple_SetItem( pPosArgs , 1 , pVal2 ) ; // nb: tuple position 0
    if (rc!=0)
        throw std::runtime_error("Can't add to tuple");

    // create a new dictionary
    PyObject* pKywdArgs = PyDict_New() ;
    if (!pKywdArgs)
        throw std::runtime_error("Can't create dictionary");

    // call our function
    PyObject* pResult = PyObject_Call( pAddFn , pPosArgs , pKywdArgs ) ;
    if (!pResult)
        throw std::runtime_error("Can't get result out of function");

    // convert the result to a string
    PyObject* pResultRepr = PyObject_Repr( pResult ) ;
    std::string result = PyEmbeddedUtils::toString(pResultRepr);

    Py_Finalize();

    return result == "30";
}
