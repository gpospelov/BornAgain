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

#include<string>

namespace BornAgain
{
    const std::string PHI_AXIS_NAME = "phi_f";
    const std::string ALPHA_AXIS_NAME = "alpha_f";
    const std::string U_AXIS_NAME = "u";
    const std::string V_AXIS_NAME = "v";
    const size_t PHI_AXIS_INDEX = 0;
    const size_t ALPHA_AXIS_INDEX = 1;
    const size_t X_AXIS_INDEX = 0;
    const size_t Y_AXIS_INDEX = 1;

    const std::string GISASSimulationType = "GISASSimulation";
    const std::string OffSpecSimulationType = "OffSpecSimulation";

    const std::string InstrumentType = "Instrument";
    const std::string DetectorType = "Detector";
    const std::string SphericalDetectorType = "SphericalDetector";
    const std::string RectangularDetectorType = "RectangularDetector";
    const std::string IsGISAXSDetectorType = "IsGISAXSDetector";
    const std::string BeamType = "Beam";

    const std::string MultiLayerType = "MultiLayer";
    const std::string LayerType = "Layer";
    const std::string LayerInterfaceType = "LayerInterface";
    const std::string ParticleLayoutType = "ParticleLayout";
    const std::string ParticleType = "Particle";
    const std::string ParticleInfoType = "ParticleInfo";
    const std::string ParticleCoreShellType = "ParticleCoreShell";
    const std::string ParticleDistributionType = "ParticleDistribution";
    const std::string ParticleCompositionType = "ParticleComposition";
    const std::string TransformationType = "Rotation";

    const std::string LayerBasicRoughnessType = "LayerBasicRoughness";
    const std::string LayerZeroRoughnessType = "LayerZeroRoughness";

    const std::string InterferenceFunctionNoneType = "InterferenceFunctionNone";
    const std::string InterferenceFunction1DLatticeType = "InterferenceFunction1DLattice";
    const std::string InterferenceFunctionRadialParaCrystalType =
            "InterferenceFunctionRadialParaCrystal";
    const std::string InterferenceFunction2DParaCrystalType = "InterferenceFunction2DParaCrystal";
    const std::string InterferenceFunction2DLatticeType = "InterferenceFunction2DLattice";

    const std::string CrystalType = "Crystal";
    const std::string MesoCrystalType = "MesoCrystal";

    const std::string AnisoPyramidType = "AnisoPyramid";
    const std::string BoxType = "Box";
    const std::string ConeType = "Cone";
    const std::string Cone6Type = "Cone6";
    const std::string CuboctahedronType = "Cuboctahedron";
    const std::string CylinderType = "Cylinder";
    const std::string EllipsoidalCylinderType = "EllipsoidalCylinder";
    const std::string FullSphereType = "FullSphere";
    const std::string FullSpheroidType = "FullSpheroid";
    const std::string FFGaussType = "FormFactorGauss";
    const std::string HemiEllipsoidType = "HemiEllipsoid";
    const std::string FFLorentzType = "FormFactorLorentz";
    const std::string Prism3Type = "Prism3";
    const std::string Prism6Type = "Prism6";
    const std::string PyramidType = "Pyramid";
    const std::string Ripple1Type = "Ripple1";
    const std::string Ripple2Type = "Ripple2";
    const std::string TetrahedronType = "Tetrahedron";
    const std::string TruncatedCubeType = "TruncatedCube";
    const std::string TruncatedSphereType = "TruncatedSphere";
    const std::string TruncatedSpheroidType = "TruncatedSpheroid";

    const std::string FormFactorCrystalType = "FormFactorCrystal";
    const std::string FormFactorSphereGaussianRadiusType = "FormFactorSphereGaussianRadius";
    const std::string FormFactorSphereLogNormalRadiusType = "FormFactorSphereLogNormalRadius";
    const std::string FormFactorSphereUniformRadiusType = "FormFactorSphereUniformRadius";
    const std::string FormFactorTrivialType = "FormFactorTrivial";
    const std::string FormFactorDWBAType = "FormFactorDWBA";
    const std::string FormFactorPolarizedDWBAType = "FormFactorDWBAPol";

    const std::string FormFactorDecoratorFactor = "FormFactorDecoratorFactor";
    const std::string FormFactorDecoratorPositionFactor = "FormFactorDecoratorPositionFactor";
    const std::string FormFactorDecoratorMultiPositionFactor =
            "FormFactorDecoratorMultiPositionFactor";
    const std::string FormFactorDecoratorRotation = "FormFactorDecoratorRotation";
    const std::string FormFactorDecoratorDebyeWaller = "FormFactorDecoratorDebyeWaller";
    const std::string FormFactorDecoratorMaterial = "FormFactorDecoratorMaterial";
    const std::string FormFactorWeighted = "FormFactorWeighted";

    const std::string XRotationType = "XRotation";
    const std::string YRotationType = "YRotation";
    const std::string ZRotationType = "ZRotation";
    const std::string EulerRotationType = "EulerRotation";

    const std::string DistributionNoneType = "DistributionNone";
    const std::string DistributionGateType = "DistributionGate";
    const std::string DistributionLorentzType = "DistributionLorentz";
    const std::string DistributionGaussianType = "DistributionGaussian";
    const std::string DistributionLogNormalType = "DistributionLogNormal";
    const std::string DistributionCosineType = "DistributionCosine";

    const std::string FTDistribution1DCauchyType = "FTDistribution1DCauchy";
    const std::string FTDistribution1DGaussType = "FTDistribution1DGauss";
    const std::string FTDistribution1DGateType = "FTDistribution1DGate";
    const std::string FTDistribution1DTriangleType = "FTDistribution1DTriangle";
    const std::string FTDistribution1DCosineType = "FTDistribution1DCosine";
    const std::string FTDistribution1DVoigtType = "FTDistribution1DVoigt";

    const std::string FTDistribution2DCauchyType = "FTDistribution2DCauchy";
    const std::string FTDistribution2DGaussType = "FTDistribution2DGauss";
    const std::string FTDistribution2DGateType = "FTDistribution2DGate";
    const std::string FTDistribution2DConeType = "FTDistribution2DCone";
    const std::string FTDistribution2DVoigtType = "FTDistribution2DVoigt";
}

#endif // BORNAGAINNAMESPACE_H


