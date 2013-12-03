#ifndef ISGISAXS08BUILDER_H
#define ISGISAXS08BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS08Builder class to build sample: 2D paracrystal lattice
//! (IsGISAXS example #8)
class IsGISAXS08Para1DBuilder : public ISampleBuilder
{
public:
    IsGISAXS08Para1DBuilder();
    ISample *buildSample() const;
};


//! The IsGISAXS08Builder class to build sample: 2D paracrystal lattice
//! with isotropic pdfs (IsGISAXS example #8)
class IsGISAXS08Para2DBuilder : public ISampleBuilder
{
public:
    IsGISAXS08Para2DBuilder();
    ISample *buildSample() const;
};


#endif // ISGISAXS08BUILDER_H
