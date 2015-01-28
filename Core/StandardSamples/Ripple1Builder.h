// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/Ripple1Builder.h
//! @brief     Defines class Ripple1Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RIPPLE1BUILDER_H
#define RIPPLE1BUILDER_H

#include "ISampleBuilder.h"

//! @class Ripple1Builder
//! @ingroup standard_samples
//! @brief Builds sample: cosine ripple within the 1D-paracrystal model

class BA_CORE_API_ Ripple1Builder : public ISampleBuilder
{
public:
    Ripple1Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_w; //width
    double m_h; //heigth
    double m_l; //length

    double m_interf_distance;
    double m_interf_width;
};

#endif // RIPPLE1BUILDER_H
