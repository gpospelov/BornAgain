// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.h
//! @brief     Defines PyEmbeddedTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYEMBEDDEDTESTFACTORY_H
#define PYEMBEDDEDTESTFACTORY_H

#include "FunctionalTestFactory.h"

//! @class PyEmbeddedTestFactory
//! @brief Collection of tests for embedded Python.

class PyEmbeddedTestFactory : public FunctionalTestFactory
{
public:
    PyEmbeddedTestFactory();
};

#endif
