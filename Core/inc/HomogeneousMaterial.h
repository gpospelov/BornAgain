#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H

#include "IMaterial.h"
#include "Types.h"

class HomogeneousMaterial : public IMaterial
{
public:
    HomogeneousMaterial(complex_t refractive_index = complex_t(1,0) );
    virtual ~HomogeneousMaterial() {}

    complex_t getRefractiveIndex() { return m_refractive_index; }


private:
    complex_t m_refractive_index;
};

#endif // HOMOGENEOUSMATERIAL_H
