#ifndef ISGISAXS15BUILDER_H
#define ISGISAXS15BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS15Builder class to build sample: size spacing correlation approximation
//! (IsGISAXS example #15)
class IsGISAXS15Builder : public ISampleBuilder
{
public:
    IsGISAXS15Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS15BUILDER_H
