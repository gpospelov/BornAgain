#ifndef ISGISAXS10BUILDER_H
#define ISGISAXS10BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS10Builder class to build sample: cylinders on top of substrate
//! with interference (IsGISAXS example #10)
class IsGISAXS10Builder : public ISampleBuilder
{
public:
    IsGISAXS10Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
};

#endif // ISGISAXS10BUILDER_H
