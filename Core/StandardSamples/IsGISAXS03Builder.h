// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS03Builder.h
//! @brief     Defines class IsGISAXS03Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS03BUILDER_H
#define ISGISAXS03BUILDER_H


#include "ISampleBuilder.h"

//! @class IsGISAXS03DWBABuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in DWBA (IsGISAXS example #3, part I)

class BA_CORE_API_ IsGISAXS03DWBABuilder : public ISampleBuilder
{
public:
    IsGISAXS03DWBABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! @class IsGISAXS03BABuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in BA (IsGISAXS example #3, part II)

class BA_CORE_API_ IsGISAXS03BABuilder : public ISampleBuilder
{
public:
    IsGISAXS03BABuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};


//! @class IsGISAXS03BASizeBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinder formfactor in BA with size distribution
//! (IsGISAXS example #3, part II)

class IsGISAXS03BASizeBuilder : public ISampleBuilder
{
public:
    IsGISAXS03BASizeBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};



#endif // ISGISAXS03BUILDER_H
