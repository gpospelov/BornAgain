// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS03Builder.h
//! @brief     Defines class IsGISAXS03Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS03BUILDER_H
#define ISGISAXS03BUILDER_H


#include "ISampleBuilder.h"

//! The IsGISAXS03DWBABuilder class to build sample: cylinder formfactor in DWBA
//! (IsGISAXS example #3, part I)
class IsGISAXS03DWBABuilder : public ISampleBuilder
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


//! The IsGISAXS03BABuilder class to build sample: cylinder formfactor in BA
//! (IsGISAXS example #3, part II)
class IsGISAXS03BABuilder : public ISampleBuilder
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


//! The IsGISAXS03BASizeBuilder class to build sample: cylinder formfactor in BA
//! with size distribution (IsGISAXS example #3, part II)
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
