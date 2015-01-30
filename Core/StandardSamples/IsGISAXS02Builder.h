// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS02Builder.h
//! @brief     Defines class IsGISAXS02Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS02BUILDER_H
#define ISGISAXS02BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS02Builder
//! @ingroup standard_samples
//! @brief Builds sample: mixture cylinder particles with different size
//! distribution (IsGISAXS example #2)

class BA_CORE_API_ IsGISAXS02Builder : public ISampleBuilder
{
public:
    IsGISAXS02Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_radius1;
    double m_radius2;
    double m_height1;
    double m_height2;
    double m_sigma1_ratio;
    double m_sigma2_ratio;
};

#endif // ISGISAXS02BUILDER_H
