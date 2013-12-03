#ifndef ISGISAXS07BUILDER_H
#define ISGISAXS07BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS07Builder class to build sample: Mixture of different particles
//! (IsGISAXS example #7)
class IsGISAXS07Builder : public ISampleBuilder
{
public:
    IsGISAXS07Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS07BUILDER_H
