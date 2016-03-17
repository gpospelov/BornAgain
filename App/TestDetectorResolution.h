// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestDetectorResolution.h
//! @brief     Defines class TestDetectorResolution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTDETECTORRESOLUTION_H_
#define TESTDETECTORRESOLUTION_H_

#include "IApplicationTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "ISample.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunctionNone.h"

class TestDetectorResolution : public IApplicationTest
{
public:
    TestDetectorResolution() : mp_intensity_output(0), mp_sample(0) {}
    virtual ~TestDetectorResolution()
    {
        delete mp_intensity_output;
        delete mp_sample;
    }
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};

#endif /* TESTDETECTORRESOLUTION_H_ */


