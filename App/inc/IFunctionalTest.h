// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/IFunctionalTest.h 
//! @brief     Defines class IFunctionalTest.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IFUNCTIONALTEST_H
#define IFUNCTIONALTEST_H

#include <string>
#include "INamed.h"

class ProgramOptions;

//! Base class for sophisticated functional tests.

//! See also FunctionalTestFactory
//!
class IFunctionalTest : public INamed
{
  public:
    IFunctionalTest() : mp_options(0) {}
    IFunctionalTest(const std::string &name) : INamed(name), mp_options(0) {}
    IFunctionalTest(const std::string &name, const std::string &title)
        : INamed(name, title), mp_options(0) {}
    virtual ~IFunctionalTest(){}

    virtual void initialise(ProgramOptions *p_options)
    { mp_options = p_options; }
    virtual void execute();
    virtual void finalise() {}
    std::string getOutputPath() const { return m_output_path; }
    void setOutputPath(const std::string &output_path)
    { m_output_path = output_path; }
  protected:
    ProgramOptions *mp_options;
    std::string m_output_path;
};

#endif // IFUNCTIONALTEST_H
