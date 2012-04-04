#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H

#include "inc/IMaterial.h"

class HomogeneousMaterial : public IMaterial
{
public:
    HomogeneousMaterial(double refractive_index = 1);
    virtual ~HomogeneousMaterial() {}

    double getRefractiveIndex() { return m_refractive_index; }


private:
    double m_refractive_index;
};

#endif // HOMOGENEOUSMATERIAL_H
