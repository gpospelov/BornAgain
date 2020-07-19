// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.h
//! @brief     Defines PyEmbeddedTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYEMBEDDED_PYEMBEDDEDTESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYEMBEDDED_PYEMBEDDEDTESTFACTORY_H

#include "Fit/TestEngine/IFactory.h"
#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! @class PyEmbeddedTestFactory
//! @brief Collection of tests for embedded Python.

class PyEmbeddedTestFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    PyEmbeddedTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_PYTHON_PYEMBEDDED_PYEMBEDDEDTESTFACTORY_H
