// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS04Builder.h
//! @brief     Defines class IsGISAXS04Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS04BUILDER_H
#define ISGISAXS04BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS04Para1DBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4)

class BA_CORE_API_ IsGISAXS04Para1DBuilder : public ISampleBuilder
{
public:
    IsGISAXS04Para1DBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_corr_peak_distance;
    double m_corr_width;
    double m_corr_length;
    double m_cylinder_height;
    double m_cylinder_radius;
};


//! @class IsGISAXS04Para2DBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4)

class BA_CORE_API_ IsGISAXS04Para2DBuilder : public ISampleBuilder
{
public:
    IsGISAXS04Para2DBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_peak_distance;
    double m_corr_length;
    double m_domain_size_1;
    double m_domain_size_2;
    double m_cylinder_height;
    double m_cylinder_radius;
};


#endif // ISGISAXS04BUILDER_H
