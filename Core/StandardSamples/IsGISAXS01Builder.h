#ifndef ISGISAXS01BUILDER_H
#define ISGISAXS01BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS01Builder class which generates sample from IsGISAXS ex01 example
//! Mixture of cylinders and prisms without interference
class IsGISAXS01Builder : public ISampleBuilder
{
public:
    IsGISAXS01Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism_height;
    double m_prism_half_side;
    double m_cylinder_weight;
};

#endif // ISGISAXS01BUILDER_H
