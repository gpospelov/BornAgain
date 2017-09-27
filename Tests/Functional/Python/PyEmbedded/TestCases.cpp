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
#include "SysUtils.h"
#include <iostream>

//! Accessing to the content of path.sys variable.

bool SysPath::runTest()
{
    std::cout << "PYTHONPATH: " << SysUtils::getenv("PYTHONPATH") << std::endl;
    std::cout << "PYTHONHOME: " << SysUtils::getenv("PYTHONHOME") << std::endl;
    std::cout << "BUILD_LIB_DIR: " << std::string(BUILD_LIB_DIR) << std::endl;

    Py_Initialize();

    PyObject *sysPath = PySys_GetObject((char*)"path");
    auto content = PyEmbeddedUtils::toVectorString(sysPath);
    for (auto s : content)
        std::cout << s << std::endl;

    Py_Finalize();

    return !content.empty();
}

//! Comparing results of GetVersionNumber() function obtained in "embedded" and "native C++" ways.

bool FunctionCall::runTest()
{

    throw std::runtime_error("XXX");

    Py_Initialize();

    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyList_Append(sysPath, PyString_FromString(BUILD_LIB_DIR));

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
    PyList_Append(sysPath, PyString_FromString(BUILD_LIB_DIR));

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

