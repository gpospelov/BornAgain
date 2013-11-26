// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPolarizedDWBAZeroMag.h
//! @brief     Defines class TestPolarizedDWBAZeroMag.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPOLARIZEDDWBAZEROMAG_H_
#define TESTPOLARIZEDDWBAZEROMAG_H_

#include "IFunctionalTest.h"
#include "OutputData.h"

#include <string>

//! TestPolarizedDWBAZeroMag: test IsGISAXS03 DWBA Cylinder form factor with
//! polarized calculation (zero magnetic field should give same results as
//! original test (TestIsGISAXS03)

class TestPolarizedDWBAZeroMag : public IFunctionalTest
{
public:
    TestPolarizedDWBAZeroMag();
    virtual ~TestPolarizedDWBAZeroMag(){}
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

    std::string m_data_path;
    OutputData<double> *m_result;

};

#endif /* TESTPOLARIZEDDWBAZEROMAG_H_ */
