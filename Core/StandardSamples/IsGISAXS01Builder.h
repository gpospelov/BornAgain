#ifndef ISGISAXS01BUILDER_H
#define ISGISAXS01BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS01Builder class which generates sample from IsGISAXS ex01 example
class IsGISAXS01Builder : public ISampleBuilder
{
public:
    IsGISAXS01Builder();
    ISample *buildSample() const;

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism_height;
    double m_prism_half_side;
    double m_cylinder_weight;
};

#endif // ISGISAXS01BUILDER_H
