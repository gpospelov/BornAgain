// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS06Builder.h
//! @brief     Defines class IsGISAXS06Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS06BUILDER_H
#define ISGISAXS06BUILDER_H

#include "ISampleBuilder.h"


//! @class IsGISAXS06Lattice1Builder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ IsGISAXS06Lattice1Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice1Builder(){}
    ISample *buildSample() const;
};


//! @class IsGISAXS06Lattice2Builder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ IsGISAXS06Lattice2Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice2Builder(){}
    ISample *buildSample() const;
};

//! @class IsGISAXS06Lattice3Builder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ IsGISAXS06Lattice3Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice3Builder(){}
    ISample *buildSample() const;
};

//! @class IsGISAXS06Lattice4Builder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ IsGISAXS06Lattice4Builder : public ISampleBuilder
{
public:
    IsGISAXS06Lattice4Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_xi;

};



#endif // ISGISAXS06BUILDER_H
