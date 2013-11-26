#ifndef POLARIZEDDWBAZEROMAGBUILDER_H
#define POLARIZEDDWBAZEROMAGBUILDER_H

#include "ISampleBuilder.h"

//! The PolarizedDWBAZeroMagBuilder class to build sample
//! without interference 
class PolarizedDWBAZeroMagBuilder : public ISampleBuilder
{
public:
    PolarizedDWBAZeroMagBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
};

#endif // ISGISAXS01BUILDER_H
