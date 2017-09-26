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

#include <Python.h>
#include "TestCases.h"
#include "BornAgainNamespace.h"
#include "BAVersion.h"
#include <iostream>

//! Comparing results of GetVersionNumber() function obtained in "embedded" and "native C++" ways.

bool FunctionCall::runTest()
{
    Py_Initialize();

    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));

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

    char* cstr = PyString_AsString(result);
    if(!cstr)
        throw std::runtime_error("Error in return type");

    std::string str(cstr);
    Py_DECREF(result);

    return str == BornAgain::GetVersionNumber();
}
