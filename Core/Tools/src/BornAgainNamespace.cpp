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

#include "BornAgainNamespace.h"

const char *BornAgain::PHI_AXIS_NAME = "phi_f";
const char *BornAgain::ALPHA_AXIS_NAME = "alpha_f";
const char *BornAgain::U_AXIS_NAME = "u";
const char *BornAgain::V_AXIS_NAME = "v";
const size_t BornAgain::X_AXIS_INDEX = 0;
const size_t BornAgain::Y_AXIS_INDEX = 1;

const char *BornAgain::GISASSimulationType = "GISASSimulation";
const char *BornAgain::OffSpecSimulationType = "OffSpecSimulation";

const char *BornAgain::InstrumentType = "Instrument";
const char *BornAgain::DetectorType = "Detector";
const char *BornAgain::SphericalDetectorType = "SphericalDetector";
const char *BornAgain::RectangularDetectorType = "RectangularDetector";
const char *BornAgain::IsGISAXSDetectorType = "IsGISAXSDetector";
const char *BornAgain::BeamType = "Beam";

const char *BornAgain::MultiLayerType = "MultiLayer";
const char *BornAgain::LayerType = "Layer";
const char *BornAgain::LayerInterfaceType = "LayerInterface";
const char *BornAgain::ParticleLayoutType = "ParticleLayout";
const char *BornAgain::ParticleType = "Particle";
const char *BornAgain::ParticleInfoType = "ParticleInfo";
const char *BornAgain::ParticleCoreShellType = "ParticleCoreShell";
const char *BornAgain::ParticleDistributionType = "ParticleDistribution";
const char *BornAgain::ParticleCompositionType = "ParticleComposition";
const char *BornAgain::TransformationType = "Rotation";

const char *BornAgain::LayerBasicRoughnessType = "LayerBasicRoughness";
const char *BornAgain::LayerZeroRoughnessType = "LayerZeroRoughness";

const char *BornAgain::InterferenceFunctionNoneType = "InterferenceFunctionNone";
const char *BornAgain::InterferenceFunction1DLatticeType = "InterferenceFunction1DLattice";
const char *BornAgain::InterferenceFunctionRadialParaCrystalType =
            "InterferenceFunctionRadialParaCrystal";
const char *BornAgain::InterferenceFunction2DParaCrystalType = "InterferenceFunction2DParaCrystal";
const char *BornAgain::InterferenceFunction2DLatticeType = "InterferenceFunction2DLattice";

const char *BornAgain::CrystalType = "Crystal";
const char *BornAgain::MesoCrystalType = "MesoCrystal";

const char *BornAgain::FFAnisoPyramidType = "AnisoPyramid";
const char *BornAgain::FFBoxType = "Box";
const char *BornAgain::FFConeType = "Cone";
const char *BornAgain::FFCone6Type = "Cone6";
const char *BornAgain::FFCuboctahedronType = "Cuboctahedron";
const char *BornAgain::FFCylinderType = "Cylinder";
const char *BornAgain::FFEllipsoidalCylinderType = "EllipsoidalCylinder";
const char *BornAgain::FFFullSphereType = "FullSphere";
const char *BornAgain::FFFullSpheroidType = "FullSpheroid";
const char *BornAgain::FFGaussType = "FormFactorGauss";
const char *BornAgain::FFHemiEllipsoidType = "HemiEllipsoid";
const char *BornAgain::FFLorentzType = "FormFactorLorentz";
const char *BornAgain::FFPrism3Type = "Prism3";
const char *BornAgain::FFPrism6Type = "Prism6";
const char *BornAgain::FFPyramidType = "Pyramid";
const char *BornAgain::FFRipple1Type = "Ripple1";
const char *BornAgain::FFRipple2Type = "Ripple2";
const char *BornAgain::FFTetrahedronType = "Tetrahedron";
const char *BornAgain::FFTruncatedCubeType = "TruncatedCube";
const char *BornAgain::FFTruncatedSphereType = "TruncatedSphere";
const char *BornAgain::FFTruncatedSpheroidType = "TruncatedSpheroid";

const char *BornAgain::FormFactorCrystalType = "FormFactorCrystal";
const char *BornAgain::FormFactorSphereGaussianRadiusType = "FormFactorSphereGaussianRadius";
const char *BornAgain::FormFactorSphereLogNormalRadiusType = "FormFactorSphereLogNormalRadius";
const char *BornAgain::FormFactorSphereUniformRadiusType = "FormFactorSphereUniformRadius";
const char *BornAgain::FormFactorTrivialType = "FormFactorTrivial";
const char *BornAgain::FormFactorDWBAType = "FormFactorDWBA";
const char *BornAgain::FormFactorPolarizedDWBAType = "FormFactorDWBAPol";

const char *BornAgain::FormFactorDecoratorFactor = "FormFactorDecoratorFactor";
const char *BornAgain::FormFactorDecoratorPositionFactor = "FormFactorDecoratorPositionFactor";
const char *BornAgain::FormFactorDecoratorMultiPositionFactor =
            "FormFactorDecoratorMultiPositionFactor";
const char *BornAgain::FormFactorDecoratorRotation = "FormFactorDecoratorRotation";
const char *BornAgain::FormFactorDecoratorDebyeWaller = "FormFactorDecoratorDebyeWaller";
const char *BornAgain::FormFactorDecoratorMaterial = "FormFactorDecoratorMaterial";
const char *BornAgain::FormFactorWeighted = "FormFactorWeighted";

const char *BornAgain::XRotationType = "XRotation";
const char *BornAgain::YRotationType = "YRotation";
const char *BornAgain::ZRotationType = "ZRotation";
const char *BornAgain::EulerRotationType = "EulerRotation";

const char *BornAgain::DistributionNoneType = "DistributionNone";
const char *BornAgain::DistributionGateType = "DistributionGate";
const char *BornAgain::DistributionLorentzType = "DistributionLorentz";
const char *BornAgain::DistributionGaussianType = "DistributionGaussian";
const char *BornAgain::DistributionLogNormalType = "DistributionLogNormal";
const char *BornAgain::DistributionCosineType = "DistributionCosine";

const char *BornAgain::FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const char *BornAgain::FTDistribution1DGaussType = "FTDistribution1DGauss";
const char *BornAgain::FTDistribution1DGateType = "FTDistribution1DGate";
const char *BornAgain::FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const char *BornAgain::FTDistribution1DCosineType = "FTDistribution1DCosine";
const char *BornAgain::FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const char *BornAgain::FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const char *BornAgain::FTDistribution2DGaussType = "FTDistribution2DGauss";
const char *BornAgain::FTDistribution2DGateType = "FTDistribution2DGate";
const char *BornAgain::FTDistribution2DConeType = "FTDistribution2DCone";
const char *BornAgain::FTDistribution2DVoigtType = "FTDistribution2DVoigt";
