#ifndef SAMPLEBUILDER_H
#define SAMPLEBUILDER_H

#include "ISampleBuilder.h"

namespace FunctionalTests {

//! Builds sample using set of input parameters.
//! Mixture of cylinders and prisms on top of substrate.
class SampleBuilder : public ISampleBuilder
{
public:
    SampleBuilder();

    virtual ~SampleBuilder(){}
    virtual ISample *buildSample() const;
protected:
    virtual void init_parameters();
private:
    double m_cylinder_height;
    double m_cylinder_radius;
    double m_prism3_length;
    double m_prism3_height;
    double m_cylinder_ratio;
};

}

#endif // SAMPLEBUILDER_H
