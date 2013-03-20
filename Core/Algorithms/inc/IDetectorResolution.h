// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IDetectorResolution.h
//! @brief     Defines class IDetectorResolution.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef IDETECTORRESOLUTION_H_
#define IDETECTORRESOLUTION_H_

#include "OutputData.h"
#include "IParameterized.h"
#include "ICloneable.h"

class IDetectorResolution : public IParameterized, public ICloneable
{
public:
    virtual ~IDetectorResolution() {}
    //! Apply the resolution function to the intensity data
    virtual void applyDetectorResolution(OutputData<double> *p_intensity_map) const=0;
    virtual IDetectorResolution *clone() const = 0;
};

#endif /* IDETECTORRESOLUTION_H_ */
