// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/IFunctionalTest.h
//! @brief     Defines class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IAPPLICATIONTEST_H
#define IAPPLICATIONTEST_H

#include <string>
#include "INamed.h"

class ProgramOptions;

//! Base class for sophisticated functional tests.

//! See also FunctionalTestFactory
//!
class IApplicationTest : public INamed
{
public:
    IApplicationTest() : mp_options(0) {}
    IApplicationTest(const std::string& name) : INamed(name), mp_options(0) {}
    virtual ~IApplicationTest(){}

    virtual void initialise(ProgramOptions *p_options)
    { mp_options = p_options; }
    virtual void execute() {}
    virtual void finalise() {}
    std::string getOutputPath() const { return m_output_path; }
    void setOutputPath(const std::string& output_path)
    { m_output_path = output_path; }
protected:
    ProgramOptions *mp_options;
    std::string m_output_path;
};


#endif // IFUNCTIONALTEST_H


