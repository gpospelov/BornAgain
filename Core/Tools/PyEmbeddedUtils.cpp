// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyEmbeddedUtils.h
//! @brief     IOmplements various functions from PyEmbeddedUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyEmbeddedUtils.h"
#include "PythonFormatting.h"
#include "MultiLayer.h"
#include "SysUtils.h"
#include <stdexcept>
#include <iostream>


std::string PyEmbeddedUtils::toString(PyObject* obj, bool decref)
{
    std::string result;
#if PY_MAJOR_VERSION >= 3
    PyObject* pyStr = PyUnicode_AsEncodedString(obj, "utf-8", "Error ~");
    result = std::string(PyBytes_AsString(pyStr));
    Py_DECREF(pyStr);
#else
    result = std::string(PyString_AsString(obj));
#endif

    if (decref)
        Py_DECREF(obj);

    return result;
}

std::vector<std::string> PyEmbeddedUtils::toVectorString(PyObject* obj, bool decref)
{
    std::vector<std::string> result;

    if (PyTuple_Check(obj)) {
        for (Py_ssize_t i = 0; i < PyTuple_Size(obj); i++) {
            PyObject *value = PyTuple_GetItem(obj, i);
            result.push_back( toString(value, false) );
        }

    } else if (PyList_Check(obj)) {
        for (Py_ssize_t i = 0; i < PyList_Size(obj); i++) {
            PyObject *value = PyList_GetItem(obj, i);
            result.push_back( toString(value, false) );
        }

    } else {
        throw std::runtime_error("PyEmbeddedUtils::toVectorString() -> Error. Unexpected object.");
    }

    if (decref)
        Py_DECREF(obj);

    return result;
}


std::string PyEmbeddedUtils::toString(char* c)
{
    if (c)
        return std::string(c);
    else
        return std::string();
}


std::string PyEmbeddedUtils::toString(wchar_t* c)
{
    if (c) {
        std::wstring wstr(c);
        std::string result( wstr.begin(), wstr.end() );
        return result;
    } else {
        return std::string();
    }
}

void PyEmbeddedUtils::import_bornagain(const std::string& path)
{
    if (!Py_IsInitialized()) {
        Py_InitializeEx(0);

        if (!path.empty()) {
            PyObject *sysPath = PySys_GetObject((char*)"path");
            PyList_Append(sysPath, PyString_FromString(path.c_str()));
        }


        // Stores signal handler before numpy's mess it up.
        // This is to make ctrl-c working from terminal.
        PyOS_sighandler_t sighandler;
#ifndef _WIN32
            sighandler = PyOS_getsig(SIGINT);
#endif
        PyObject* pmod = PyImport_ImportModule("bornagain");
        if (!pmod) {
            PyErr_Print();
            throw std::runtime_error("Can't load bornagain");
        }

        // restores single handler to make ctr-c alive.
#ifndef _WIN32
            PyOS_setsig(SIGINT, sighandler);
#endif

    }

}
