#include "Compare.h"

Compare::Compare()
{

}

bool Compare::compareFormFactor(const IFormFactor *iFormFactor1, const IFormFactor *iFormFactor2)
{
    if (const FormFactorAnisoPyramid *a = dynamic_cast<const FormFactorAnisoPyramid *>(iFormFactor1))
    {
        if (const FormFactorAnisoPyramid *b = dynamic_cast<const FormFactorAnisoPyramid *>(iFormFactor2))
             return compareFormFactorAnisoPyramid(a,b);
        else
            return 0;
    }

    else if (const FormFactorBox *c = dynamic_cast<const FormFactorBox *>(iFormFactor1))
    {
        if (const FormFactorBox *d = dynamic_cast<const FormFactorBox *>(iFormFactor2))
             return compareFormFactorBox(c,d);
        else
            return 0;
    }

    else if (const FormFactorCone *a = dynamic_cast<const FormFactorCone *>(iFormFactor1))
    {
        if (const FormFactorCone *b = dynamic_cast<const FormFactorCone *>(iFormFactor2))
             return compareFormFactorCone(a,b);
        else
            return 0;
    }

    else if (const FormFactorCone6 *a = dynamic_cast<const FormFactorCone6 *>(iFormFactor1))
    {
        if (const FormFactorCone6 *b = dynamic_cast<const FormFactorCone6 *>(iFormFactor2))
             return compareFormFactorCone6(a,b);
        else
            return 0;
    }

    else if (const FormFactorCuboctahedron *a = dynamic_cast<const FormFactorCuboctahedron *>(iFormFactor1))
    {
        if (const FormFactorCuboctahedron *b = dynamic_cast<const FormFactorCuboctahedron *>(iFormFactor2))
             return compareFormFactorCuboctahedron(a,b);
        else
            return 0;
    }

    else if (const FormFactorCylinder *a = dynamic_cast<const FormFactorCylinder *>(iFormFactor1))
    {
        if (const FormFactorCylinder *b = dynamic_cast<const FormFactorCylinder *>(iFormFactor2))
             return compareFormFactorCylinder(a,b);
        else
            return 0;
    }

    else if (const FormFactorEllipsoidalCylinder *a = dynamic_cast<const FormFactorEllipsoidalCylinder *>(iFormFactor1))
    {
        if (const FormFactorEllipsoidalCylinder *b = dynamic_cast<const FormFactorEllipsoidalCylinder *>(iFormFactor2))
             return compareFormFactorEllipsoidalCylinder(a,b);
        else
            return 0;
    }

    else if (const FormFactorFullSphere *a = dynamic_cast<const FormFactorFullSphere *>(iFormFactor1))
    {
        if (const FormFactorFullSphere *b = dynamic_cast<const FormFactorFullSphere *>(iFormFactor2))
             return compareFormFactorFullSphere(a,b);
        else
            return 0;
    }

    else if (const FormFactorFullSpheroid *a = dynamic_cast<const FormFactorFullSpheroid *>(iFormFactor1))
    {
        if (const FormFactorFullSpheroid *b = dynamic_cast<const FormFactorFullSpheroid *>(iFormFactor2))
             return compareFormFactorFullSpheroid(a,b);
        else
            return 0;
    }

    else if (const FormFactorGauss *a = dynamic_cast<const FormFactorGauss *>(iFormFactor1))
    {
        if (const FormFactorGauss *b = dynamic_cast<const FormFactorGauss *>(iFormFactor2))
             return compareFormFactorGauss(a,b);
        else
            return 0;
    }

    else if (const FormFactorHemiEllipsoid *a = dynamic_cast<const FormFactorHemiEllipsoid *>(iFormFactor1))
    {
        if (const FormFactorHemiEllipsoid *b = dynamic_cast<const FormFactorHemiEllipsoid *>(iFormFactor2))
             return compareFormFactorHemiEllipsoid(a,b);
        else
            return 0;
    }

    else if (const FormFactorInfLongBox *a = dynamic_cast<const FormFactorInfLongBox *>(iFormFactor1))
    {
        if (const FormFactorInfLongBox *b = dynamic_cast<const FormFactorInfLongBox *>(iFormFactor2))
             return compareFormFactorInfLongBox(a,b);
        else
            return 0;
    }

    else if (const FormFactorInfLongRipple1 *a = dynamic_cast<const FormFactorInfLongRipple1 *>(iFormFactor1))
    {
        if (const FormFactorInfLongRipple1 *b = dynamic_cast<const FormFactorInfLongRipple1 *>(iFormFactor2))
             return compareFormFactorInfLongRipple1(a,b);
        else
            return 0;
    }

    else if (const FormFactorInfLongRipple2 *a = dynamic_cast<const FormFactorInfLongRipple2 *>(iFormFactor1))
    {
        if (const FormFactorInfLongRipple2 *b = dynamic_cast<const FormFactorInfLongRipple2 *>(iFormFactor2))
             return compareFormFactorInfLongRipple2(a,b);
        else
            return 0;
    }

    else if (const FormFactorLorentz *a = dynamic_cast<const FormFactorLorentz *>(iFormFactor1))
    {
        if (const FormFactorLorentz *b = dynamic_cast<const FormFactorLorentz *>(iFormFactor2))
             return compareFormFactorLorrentz(a,b);
        else
            return 0;
    }

    else if (const FormFactorPrism3 *a = dynamic_cast<const FormFactorPrism3 *>(iFormFactor1))
    {
        if (const FormFactorPrism3 *b = dynamic_cast<const FormFactorPrism3 *>(iFormFactor2))
             return compareFormFactorPrism3(a,b);
        else
            return 0;
    }

    else if (const FormFactorPrism6 *a = dynamic_cast<const FormFactorPrism6 *>(iFormFactor1))
    {
        if (const FormFactorPrism6 *b = dynamic_cast<const FormFactorPrism6 *>(iFormFactor2))
             return compareFormFactorPrism6(a,b);
        else
            return 0;
    }

    else if (const FormFactorPyramid *a = dynamic_cast<const FormFactorPyramid *>(iFormFactor1))
    {
        if (const FormFactorPyramid *b = dynamic_cast<const FormFactorPyramid *>(iFormFactor2))
             return compareFormFactorPyramid(a,b);
        else
            return 0;
    }

    else if (const FormFactorRipple1 *a = dynamic_cast<const FormFactorRipple1 *>(iFormFactor1))
    {
        if (const FormFactorRipple1 *b = dynamic_cast<const FormFactorRipple1 *>(iFormFactor2))
             return compareFormFactorRipple1(a,b);
        else
            return 0;
    }

    else if (const FormFactorRipple2 *a = dynamic_cast<const FormFactorRipple2 *>(iFormFactor1))
    {
        if (const FormFactorRipple2 *b = dynamic_cast<const FormFactorRipple2 *>(iFormFactor2))
             return compareFormFactorRipple2(a,b);
        else
            return 0;
    }

    else if (const FormFactorTetrahedron *a = dynamic_cast<const FormFactorTetrahedron *>(iFormFactor1))
    {
        if (const FormFactorTetrahedron *b = dynamic_cast<const FormFactorTetrahedron *>(iFormFactor2))
             return compareFormFactorTetrahedron(a,b);
        else
            return 0;
    }

    else if (const FormFactorTruncatedSphere *a = dynamic_cast<const FormFactorTruncatedSphere *>(iFormFactor1))
    {
        if (const FormFactorTruncatedSphere *b = dynamic_cast<const FormFactorTruncatedSphere *>(iFormFactor2))
             return compareFormFactorTruncatedSphere(a,b);
        else
            return 0;
    }

    else if (const FormFactorTruncatedSpheroid *a = dynamic_cast<const FormFactorTruncatedSpheroid *>(iFormFactor1))
    {
        if (const FormFactorTruncatedSpheroid *b = dynamic_cast<const FormFactorTruncatedSpheroid *>(iFormFactor2))
             return compareFormFactorTruncatedSpheroid(a,b);
        else
            return 0;
    }
    else
        return 0;
    //We should implement return of Exception here

}

bool Compare::compareFormFactorAnisoPyramid(const FormFactorAnisoPyramid *a, const FormFactorAnisoPyramid *b)
{
    if(a->getLength() == b->getLength() && a->getWidth() == b->getWidth()
            && a->getHeight() == b->getHeight() && a->getAlpha() == b->getAlpha())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorBox(const FormFactorBox *a,const FormFactorBox *b)
{
    if(a->getLength() == b->getLength() && a->getWidth() == b->getWidth()
            && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorCone(const FormFactorCone *a,const FormFactorCone *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight()
            && a->getAlpha() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorCone6(const FormFactorCone6 *a,const FormFactorCone6 *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight()
            && a->getAlpha() == b->getAlpha())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorCuboctahedron(const FormFactorCuboctahedron *a,const FormFactorCuboctahedron *b)
{
    if(a->getLength() == b->getLength() && a->getHeight() == b->getHeight()
            && a->getHeightRatio() == b->getHeightRatio() && a->getAlpha() == b->getAlpha())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorCylinder(const FormFactorCylinder *a,const FormFactorCylinder *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorEllipsoidalCylinder(const FormFactorEllipsoidalCylinder *a,const FormFactorEllipsoidalCylinder *b)
{
    if(a->getRadiusA() == b->getRadiusA() && a->getRadiusB() == b->getRadiusB()
            && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorFullSphere(const FormFactorFullSphere *a,const FormFactorFullSphere *b)
{
    if(a->getRadius() == b->getRadius())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorFullSpheroid(const FormFactorFullSpheroid *a,const FormFactorFullSpheroid *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorGauss(const FormFactorGauss *a,const FormFactorGauss *b)
{
    if(a->getRadius() == b->getRadius() && a->getRadius() == b->getRadius())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorHemiEllipsoid(const FormFactorHemiEllipsoid *a,const FormFactorHemiEllipsoid *b)
{
    if(a->getRadiusA() == b->getRadiusA() && a->getRadiusB() == b->getRadiusB()
            && b->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorInfLongBox(const FormFactorInfLongBox *a,const FormFactorInfLongBox *b)
{
    if(a->getWidth() == b->getWidth() && a->getHeight() == b->getWidth())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorInfLongRipple1(const FormFactorInfLongRipple1 *a,const FormFactorInfLongRipple1 *b)
{
    if(a->getWidth() == b->getWidth() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorInfLongRipple2(const FormFactorInfLongRipple2 *a,const FormFactorInfLongRipple2 *b)
{
    if(a->getWidth() == b->getWidth() && a->getHeight() == b->getHeight()
            && a->getAsymetry() == b->getAsymetry())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorLorrentz(const FormFactorLorentz *a,const FormFactorLorentz *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorPrism3(const FormFactorPrism3 *a,const FormFactorPrism3 *b)
{
    if(a->getLength() == b->getLength() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorPrism6(const FormFactorPrism6 *a,const FormFactorPrism6 *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorPyramid(const FormFactorPyramid *a,const FormFactorPyramid *b)
{
    if(a->getLength() == b->getLength() && a->getHeight() == b->getHeight()
            && a->getAlpha() == b->getAlpha())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorRipple1(const FormFactorRipple1 *a,const FormFactorRipple1 *b)
{
    if(a->getLength() == b->getLength() && a->getWidth() == b->getWidth()
            && a->getHeight() == b->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorRipple2(const FormFactorRipple2 *a,const FormFactorRipple2 *b)
{
    if(a->getLength() == b->getLength() && a->getWidth() == b->getWidth()
            && a->getHeight() == b->getHeight() && a->getAsymmetry() == b->getAsymmetry())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorTetrahedron(const FormFactorTetrahedron *a,const FormFactorTetrahedron *b)
{
    if(a->getLength() == b->getLength() && a->getHeight() == b->getHeight()
            && a->getAlpha() == b->getAlpha())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorTruncatedSphere(const FormFactorTruncatedSphere *a,const FormFactorTruncatedSphere *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight())
        return 1;
    else
        return 0;
}

bool Compare::compareFormFactorTruncatedSpheroid(const FormFactorTruncatedSpheroid *a,const FormFactorTruncatedSpheroid *b)
{
    if(a->getRadius() == b->getRadius() && a->getHeight() == b->getHeight()
            && a->getHeightFlattening() == b->getHeightFlattening())
        return 1;
    else
        return 0;
}

bool Compare::compareMaterial(const IMaterial *a,const IMaterial *b)
{
    if(a->getRefractiveIndex() == b->getRefractiveIndex() && a->getName() == b->getName())
        return 1;
    else
        return 0;
}

bool Compare::compareParticle(const Particle *a,const Particle *b)
{
    if (compareMaterial(a->getMaterial(),b->getMaterial()) == 1
            && compareFormFactor(a->getSimpleFormFactor(),b->getSimpleFormFactor()) == 1)
        return 1;
    else
        return 0;
}

bool Compare::compareParticleLayout(const ParticleLayout *a,const ParticleLayout *b)
{
    bool check = 1;
    size_t aParticles = a->getNumberOfParticles();
    size_t bParticles = a->getNumberOfParticles();
    if (aParticles != bParticles)
    {
        check = 0;
    }
    size_t particleIndex = 0;
    while (particleIndex != aParticles && check == 1)
    {
        const ParticleInfo *aInfo = a->getParticleInfo(particleIndex);
        const ParticleInfo *bInfo = b->getParticleInfo(particleIndex);
        if(aInfo->getAbundance() != bInfo->getAbundance()
            || aInfo->getDepth() != bInfo->getDepth()
            || compareParticle(aInfo->getParticle(),bInfo->getParticle()) != 1)
        {
            check = 0;
        }
    }

    if (check == 1)
        return 1;
    else
        return 0;
}
