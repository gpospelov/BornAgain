// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/Ripple2Builder.h
//! @brief     Defines class Ripple2Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RIPPLE2BUILDER_H
#define RIPPLE2BUILDER_H

#include "ISampleBuilder.h"

//! @class Ripple2Builder
//! @ingroup standard_samples
//! @brief Builds sample: triangular ripple within the 1D-paracrystal model
//! (from PRB 85, 235415, 2012)

class BA_CORE_API_ Ripple2Builder : public ISampleBuilder
{
public:
    Ripple2Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_w; //width
    double m_h; //heigth
    double m_l; //length
    double m_d; //asymetry
    double m_interf_distance;
    double m_interf_width;
};

#endif // RIPPLE2BUILDER_H
