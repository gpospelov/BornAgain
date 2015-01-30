// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFormFactors.h
//! @brief     Defines class TestFormFactors.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFORMFACTORS_H
#define TESTFORMFACTORS_H

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"

class Simulation;
class IFormFactor;
//! Comparison of form factor for different particle shapes

class TestFormFactors : public IApplicationTest
{
public:
    TestFormFactors();

    virtual ~TestFormFactors(){}

    virtual void execute();
    virtual void finalise();
private:
    // structure to hold info over several compare cases
    struct CompareStruct
    {
        CompareStruct(std::string _isginame,
                      std::string _thisname,
                      std::string _descr)
        : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    //! run isgisaxs simulation
    void run_isgisaxs_simulation(IFormFactor* p_form_factor = 0);

protected:
 IFormFactor* mp_form_factor;

};

#endif // TESTFORMFACTORS_H


