#ifndef NANOPARTICLE_H
#define NANOPARTICLE_H

#include "ISample.h"
#include "IFormFactor.h"

class NanoParticle : public ISample
{
public:
    NanoParticle();
    virtual ~NanoParticle();

private:
    IFormFactor* mp_form_factor;
};

#endif // NANOPARTICLE_H
