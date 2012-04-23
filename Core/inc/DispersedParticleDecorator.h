#ifndef DISPERSEDPARTICLEDECORATOR_H
#define DISPERSEDPARTICLEDECORATOR_H

#include "ISample.h"

class DispersedParticleDecorator : public ISample
{
public:
    DispersedParticleDecorator(ISample* p_sub_sample);
    virtual ~DispersedParticleDecorator() {}

    ISample* getSubSample() const { return mp_sub_sample; }

private:
    ISample* mp_sub_sample;

};

#endif // DISPERSEDPARTICLEDECORATOR_H
