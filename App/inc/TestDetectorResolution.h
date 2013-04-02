// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestDetectorResolution.h
//! @brief     Defines class TestDetectorResolution.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTDETECTORRESOLUTION_H_
#define TESTDETECTORRESOLUTION_H_

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunctionNone.h"

class TestDetectorResolution : public IFunctionalTest
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


