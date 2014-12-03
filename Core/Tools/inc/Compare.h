#ifndef COMPARE_H
#define COMPARE_H
#include<iostream>
#include "FormFactors.h"
#include "Materials.h"
#include "IParticle.h"
#include "ParticleLayout.h"
#include "ParticleInfo.h"

class Compare
{
public:
    Compare();
    bool compareFormFactor(const IFormFactor *iFormFactor1, const IFormFactor *iFormFactor2);
    bool compareFormFactorAnisoPyramid(const FormFactorAnisoPyramid *a, const FormFactorAnisoPyramid *b);
    bool compareFormFactorBox(const FormFactorBox *a,const FormFactorBox *b);
    bool compareFormFactorCone(const FormFactorCone *a,const FormFactorCone *b);
    bool compareFormFactorCone6(const FormFactorCone6 *a,const FormFactorCone6 *b);
    bool compareFormFactorCuboctahedron(const FormFactorCuboctahedron *a,const FormFactorCuboctahedron *b);
    bool compareFormFactorCylinder(const FormFactorCylinder *a,const FormFactorCylinder *b);
    bool compareFormFactorEllipsoidalCylinder(const FormFactorEllipsoidalCylinder *a,const FormFactorEllipsoidalCylinder *b);
    bool compareFormFactorFullSphere(const FormFactorFullSphere *a,const FormFactorFullSphere *b);
    bool compareFormFactorFullSpheroid(const FormFactorFullSpheroid *a,const FormFactorFullSpheroid *b);
    bool compareFormFactorGauss(const FormFactorGauss *a,const FormFactorGauss *b);
    bool compareFormFactorHemiEllipsoid(const FormFactorHemiEllipsoid *a,const FormFactorHemiEllipsoid *b);
    bool compareFormFactorInfLongBox(const FormFactorInfLongBox *a,const FormFactorInfLongBox *b);
    bool compareFormFactorInfLongRipple1(const FormFactorInfLongRipple1 *a,const FormFactorInfLongRipple1 *b);
    bool compareFormFactorInfLongRipple2(const FormFactorInfLongRipple2 *a,const FormFactorInfLongRipple2 *b);
    bool compareFormFactorLorrentz(const FormFactorLorentz *a,const FormFactorLorentz *b);
    bool compareFormFactorPrism3(const FormFactorPrism3 *a,const FormFactorPrism3 *b);
    bool compareFormFactorPrism6(const FormFactorPrism6 *a,const FormFactorPrism6 *b);
    bool compareFormFactorPyramid(const FormFactorPyramid *a,const FormFactorPyramid *b);
    bool compareFormFactorRipple1(const FormFactorRipple1 *a,const FormFactorRipple1 *b);
    bool compareFormFactorRipple2(const FormFactorRipple2 *a,const FormFactorRipple2 *b);
    bool compareFormFactorTetrahedron(const FormFactorTetrahedron *a,const FormFactorTetrahedron *b);
    bool compareFormFactorTruncatedSphere(const FormFactorTruncatedSphere *a,const FormFactorTruncatedSphere *b);
    bool compareFormFactorTruncatedSpheroid(const FormFactorTruncatedSpheroid *a,const FormFactorTruncatedSpheroid *b);
    bool compareMaterial(const IMaterial *a,const IMaterial *b);
    bool compareParticle(const IParticle *a,const IParticle *b);
    bool compareParticleLayout(const ParticleLayout *a, const ParticleLayout *b);
};


#endif // COMPARE_H
