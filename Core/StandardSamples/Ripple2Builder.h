#ifndef RIPPLE2BUILDER_H
#define RIPPLE2BUILDER_H

#include "ISampleBuilder.h"

//! The Ripple2Builder class to build sample: triangular ripple
//! within the 1D-paracrystal model (from PRB 85, 235415, 2012)
class Ripple2Builder : public ISampleBuilder
{
public:
    Ripple2Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_w; //width
    double m_h; //heigth
    double m_l; //length
    double m_d; //asymetry
    double m_interf_distance;
    double m_interf_width;
};

#endif // RIPPLE2BUILDER_H
