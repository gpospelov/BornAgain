// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/BornAgainNamespace.h
//! @brief     Defines BornAgain namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAINNAMESPACE_H
#define BORNAGAINNAMESPACE_H

#include <cstddef>

namespace BornAgain
{
    extern const char* PHI_AXIS_NAME;
    extern const char* ALPHA_AXIS_NAME;
    extern const char* U_AXIS_NAME;
    extern const char* V_AXIS_NAME;
    extern const size_t X_AXIS_INDEX;
    extern const size_t Y_AXIS_INDEX;

    extern const char *GISASSimulationType;
    extern const char* OffSpecSimulationType;

    extern const char* InstrumentType;
    extern const char* DetectorType;
    extern const char* SphericalDetectorType;
    extern const char* RectangularDetectorType;
    extern const char* IsGISAXSDetectorType;
    extern const char* BeamType;

    extern const char* MultiLayerType;
    extern const char* LayerType;
    extern const char* LayerInterfaceType;
    extern const char* ParticleLayoutType;
    extern const char* ParticleType;
    extern const char* ParticleInfoType;
    extern const char* ParticleCoreShellType;
    extern const char* ParticleDistributionType;
    extern const char* ParticleCompositionType;
    extern const char* TransformationType;

    extern const char* LayerBasicRoughnessType;
    extern const char* LayerZeroRoughnessType;

    extern const char* InterferenceFunctionNoneType;
    extern const char* InterferenceFunction1DLatticeType;
    extern const char* InterferenceFunctionRadialParaCrystalType;
    extern const char* InterferenceFunction2DParaCrystalType;
    extern const char* InterferenceFunction2DLatticeType;

    extern const char* CrystalType;
    extern const char* MesoCrystalType;

    extern const char* FFAnisoPyramidType;
    extern const char* FFBoxType;
    extern const char* FFConeType;
    extern const char* FFCone6Type;
    extern const char* FFCuboctahedronType;
    extern const char* FFCylinderType;
    extern const char* FFEllipsoidalCylinderType;
    extern const char* FFFullSphereType;
    extern const char* FFFullSpheroidType;
    extern const char* FFGaussType;
    extern const char* FFHemiEllipsoidType;
    extern const char* FFLorentzType;
    extern const char* FFPrism3Type;
    extern const char* FFPrism6Type;
    extern const char* FFPyramidType;
    extern const char* FFRipple1Type;
    extern const char* FFRipple2Type;
    extern const char* FFTetrahedronType;
    extern const char* FFTruncatedCubeType;
    extern const char* FFTruncatedSphereType;
    extern const char* FFTruncatedSpheroidType;

    extern const char* FormFactorCrystalType;
    extern const char* FormFactorSphereGaussianRadiusType;
    extern const char* FormFactorSphereLogNormalRadiusType;
    extern const char* FormFactorSphereUniformRadiusType;
    extern const char* FormFactorTrivialType;
    extern const char* FormFactorDWBAType;
    extern const char* FormFactorPolarizedDWBAType;

    extern const char* FormFactorDecoratorFactor;
    extern const char* FormFactorDecoratorPositionFactor;
    extern const char* FormFactorDecoratorMultiPositionFactor;
    extern const char* FormFactorDecoratorRotation;
    extern const char* FormFactorDecoratorDebyeWaller;
    extern const char* FormFactorDecoratorMaterial;
    extern const char* FormFactorWeighted;

    extern const char* XRotationType;
    extern const char* YRotationType;
    extern const char* ZRotationType;
    extern const char* EulerRotationType;

    extern const char* DistributionNoneType;
    extern const char* DistributionGateType;
    extern const char* DistributionLorentzType;
    extern const char* DistributionGaussianType;
    extern const char* DistributionLogNormalType;
    extern const char* DistributionCosineType;

    extern const char* FTDistribution1DCauchyType;
    extern const char* FTDistribution1DGaussType;
    extern const char* FTDistribution1DGateType;
    extern const char* FTDistribution1DTriangleType;
    extern const char* FTDistribution1DCosineType;
    extern const char* FTDistribution1DVoigtType;

    extern const char* FTDistribution2DCauchyType;
    extern const char* FTDistribution2DGaussType;
    extern const char* FTDistribution2DGateType;
    extern const char* FTDistribution2DConeType;
    extern const char* FTDistribution2DVoigtType;
}

#endif // BORNAGAINNAMESPACE_H


