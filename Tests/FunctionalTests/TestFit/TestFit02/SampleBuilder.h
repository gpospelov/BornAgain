#ifndef SAMPLEBUILDER_H
#define SAMPLEBUILDER_H

#include "ISampleBuilder.h"

//! builds sample using set of input parameters
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
    double m_prism3_half_side;
    double m_prism3_height;
    double m_cylinder_ratio;
};



#endif // SAMPLEBUILDER_H
