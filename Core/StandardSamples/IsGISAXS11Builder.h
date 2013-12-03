#ifndef ISGISAXS11BUILDER_H
#define ISGISAXS11BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS01Builder class to build sample: Core Shell Nanoparticles
//! (IsGISAXS example #11)
class IsGISAXS11Builder : public ISampleBuilder
{
public:
    IsGISAXS11Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS11BUILDER_H
