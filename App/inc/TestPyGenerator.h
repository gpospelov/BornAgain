// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPyGenerator.h
//! @brief     Defines class TestPyGenerator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPYGENERATOR_H
#define TESTPYGENERATOR_H
#include "IApplicationTest.h"
#include "PyGenVisitor.h"

class MultiLayer;

class TestPyGenerator : public IApplicationTest
{
public:
    TestPyGenerator();
    virtual ~TestPyGenerator(){}
    virtual void execute();

private:
    std::list<std::string> testSamples;


};

#endif //

