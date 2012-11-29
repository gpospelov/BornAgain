#ifndef IDETECTORRESOLUTION_H_
#define IDETECTORRESOLUTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IDetectorResolution.h
//! @brief  Definition of IDetectorResolution interface
//! @author Scientific Computing Group at FRM II
//! @date   Jul 10, 2012

#include "OutputData.h"
#include "IParameterized.h"

class IDetectorResolution : public IParameterized
{
public:
    //! Destructor
    virtual ~IDetectorResolution() {}
    //! Apply the resolution function to the intensity data
    virtual void applyDetectorResolution(OutputData<double> *p_intensity_map) const=0;
    virtual IDetectorResolution *clone() const = 0;
private:
    IDetectorResolution &operator=(const IDetectorResolution &);
};


#endif /* IDETECTORRESOLUTION_H_ */
