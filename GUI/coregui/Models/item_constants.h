// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/item_constants.h
//! @brief     Defines item constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEM_CONSTANTS_H
#define ITEM_CONSTANTS_H

#include <QString>

namespace Constants {

// --- Items -------------------------------------------------------------------

using ModelType = QString;

const ModelType LayerType = "Layer";
const ModelType MultiLayerType = "MultiLayer";
const ModelType ParticleType = "Particle";
const ModelType ParticleLayoutType = "ParticleLayout";
const ModelType ParticleCoreShellType = "ParticleCoreShell";
const ModelType ParticleDistributionType = "ParticleDistribution";
const ModelType ParticleCompositionType = "ParticleComposition";
const ModelType TransformationType = "Rotation";
const ModelType InterferenceFunctionRadialParaCrystalType = "InterferenceRadialParaCrystal";
const ModelType InterferenceFunction2DParaCrystalType = "Interference2DParaCrystal";
const ModelType InterferenceFunction1DLatticeType = "Interference1DLattice";
const ModelType InterferenceFunction2DLatticeType = "Interference2DLattice";
const ModelType InstrumentType = "Instrument";
const ModelType DetectorType = "Detector";
const ModelType BeamType = "Beam";

const ModelType FormFactorType = "FormFactor";
const ModelType AnisoPyramidType = "AnisoPyramid";
const ModelType BoxType = "Box";
const ModelType ConeType = "Cone";
const ModelType Cone6Type = "Cone6";
const ModelType CuboctahedronType = "Cuboctahedron";
const ModelType CylinderType = "Cylinder";
const ModelType DodecahedronType = "Dodecahedron";
const ModelType EllipsoidalCylinderType = "EllipsoidalCylinder";
const ModelType FullSphereType = "FullSphere";
const ModelType FullSpheroidType = "FullSpheroid";
const ModelType HemiEllipsoidType = "HemiEllipsoid";
const ModelType IcosahedronType = "Icosahedron";
const ModelType Prism3Type = "Prism3";
const ModelType Prism6Type = "Prism6";
const ModelType PyramidType = "Pyramid";
const ModelType Ripple1Type = "Ripple1";
const ModelType Ripple2Type = "Ripple2";
const ModelType TetrahedronType = "Tetrahedron";
const ModelType TruncatedCubeType = "TruncatedCube";
const ModelType TruncatedSphereType = "TruncatedSphere";
const ModelType TruncatedSpheroidType = "TruncatedSpheroid";

const ModelType XRotationType = "XRotation";
const ModelType YRotationType = "YRotation";
const ModelType ZRotationType = "ZRotation";
const ModelType EulerRotationType = "EulerRotation";

const ModelType PropertyType = "Property";
const ModelType VectorType = "Vector";
const ModelType GroupItemType = "GroupProperty";

const ModelType LayerBasicRoughnessType = "LayerBasicRoughness";
const ModelType LayerZeroRoughnessType = "LayerZeroRoughness";

const ModelType SphericalDetectorType = "SphericalDetector";
const ModelType RectangularDetectorType = "RectangularDetector";

const ModelType DistributionNoneType = "DistributionNone";
const ModelType DistributionGateType = "DistributionGate";
const ModelType DistributionLorentzType = "DistributionLorentz";
const ModelType DistributionGaussianType = "DistributionGaussian";
const ModelType DistributionLogNormalType = "DistributionLogNormal";
const ModelType DistributionCosineType = "DistributionCosine";

const ModelType FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const ModelType FTDistribution1DGaussType = "FTDistribution1DGauss";
const ModelType FTDistribution1DGateType = "FTDistribution1DGate";
const ModelType FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const ModelType FTDistribution1DCosineType = "FTDistribution1DCosine";
const ModelType FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const ModelType FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const ModelType FTDistribution2DGaussType = "FTDistribution2DGauss";
const ModelType FTDistribution2DGateType = "FTDistribution2DGate";
const ModelType FTDistribution2DConeType = "FTDistribution2DCone";
const ModelType FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const ModelType FTDecayFunction1DCauchyType = "FTDecayFunction1DCauchy";
const ModelType FTDecayFunction1DGaussType = "FTDecayFunction1DGauss";
const ModelType FTDecayFunction1DTriangleType = "FTDecayFunction1DTriangle";
const ModelType FTDecayFunction1DVoigtType = "FTDecayFunction1DVoigt";

const ModelType FTDecayFunction2DCauchyType = "FTDecayFunction2DCauchy";
const ModelType FTDecayFunction2DGaussType = "FTDecayFunction2DGauss";
const ModelType FTDecayFunction2DVoigtType = "FTDecayFunction2DVoigt";

const ModelType BasicLatticeType = "BasicLatticeType";
const ModelType SquareLatticeType = "SquareLatticeType";
const ModelType HexagonalLatticeType = "HexagonalLatticeType";

const ModelType MaterialType = "Material";
const ModelType HomogeneousMaterialType = "Homogeneous Material";
const ModelType HomogeneousMagneticMaterialType = "Homogeneous Magnetic Material";

const ModelType RefractiveIndexType = "RefractiveIndex";

const ModelType MagneticFieldType = "MagneticField";

const ModelType ParameterContainerType = "Parameter Container";
const ModelType ParameterType = "Parameter";
const ModelType ParameterLabelType = "Parameter Label";

const ModelType FitParameterContainerType = "FitParameterContainer";
const ModelType FitParameterType = "FitParameter";
const ModelType FitParameterLinkType = "FitParameterLink";
const ModelType FitSuiteType = "FitSuite";

const ModelType JobItemType = "JobItem";
const ModelType IntensityDataType = "IntensityData";

const ModelType BasicAxisType = "BasicAxis";
const ModelType AmplitudeAxisType = "AmplitudeAxis";

const ModelType BeamDistributionType = "BeamDistribution";
const ModelType BeamWavelengthType = "BeamWavelength";
const ModelType BeamAzimuthalAngleType = "BeamAzimuthalAngle";
const ModelType BeamInclinationAngleType = "BeamInclinationAngle";

const ModelType ResolutionFunctionNoneType = "ResolutionFunctionNone";
const ModelType ResolutionFunction2DGaussianType = "ResolutionFunction2DGaussian";

const ModelType MaskContainerType = "MaskContainer";
const ModelType RectangleMaskType = "RectangleMask";
const ModelType PolygonMaskType = "PolygonMask";
const ModelType PolygonPointType = "PolygonPoint";
const ModelType EllipseMaskType = "EllipseMask";
const ModelType VerticalLineMaskType = "VerticalLineMask";
const ModelType HorizontalLineMaskType = "HorizontalLineMask";
const ModelType MaskAllType = "MaskAllMask";

const ModelType RegionOfInterestType = "RegionOfInterest";

const ModelType SimulationOptionsType = "SimulationOptions";

const ModelType RealDataType = "RealData";
const ModelType LinkInstrumentType = "LinkInstrument";

const ModelType MinimizerContainerType = "MinimizerContainer";
const ModelType MinuitMinimizerType = "Minuit2";
const ModelType GSLMultiMinimizerType = "GSLMultiMin";
const ModelType GSLLMAMinimizerType = "GSLLMA";
const ModelType GSLSimAnMinimizerType = "GSLSimAn";
const ModelType GeneticMinimizerType = "Genetic";
const ModelType TestMinimizerType = "Test";

// --- Groups ------------------------------------------------------------------

const ModelType FormFactorGroup = "Form Factor";
const ModelType RotationGroup = "Rotation group";
const ModelType LayerRoughnessGroup = "Roughness";
const ModelType DetectorGroup = "Detector group";
const ModelType DistributionGroup = "Distribution group";
const ModelType DistributionExtendedGroup = "Distribution extended group";
const ModelType FTDistribution1DGroup = "PDF 1D";
const ModelType FTDistribution2DGroup = "PDF 2D";
const ModelType FTDecayFunction1DGroup = "Decay function 1D";
const ModelType FTDecayFunction2DGroup = "Decay function 2D";
const ModelType LatticeGroup = "Lattice group";
const ModelType MaterialGroup = "Material group";
const ModelType ResolutionFunctionGroup = "Resolution function group";
const ModelType MinimizerLibraryGroup = "Minimizer library group";

// --- Units&Constants----------------------------------------------------------
const ModelType UnitsNbins = "nbins";
const ModelType UnitsRadians = "Radians";
const ModelType UnitsDegrees = "Degrees";
const ModelType UnitsMm = "mm";
const ModelType UnitsQyQz = "Qy,Qz";

const ModelType STATUS_IDLE = "Idle";
const ModelType STATUS_RUNNING = "Running";
const ModelType STATUS_FITTING = "Fitting";
const ModelType STATUS_COMPLETED = "Completed";
const ModelType STATUS_CANCELED = "Canceled";
const ModelType STATUS_FAILED = "Failed";

const ModelType GRADIENT_GRAYSCALE = "Grayscale";
const ModelType GRADIENT_HOT = "Hot";
const ModelType GRADIENT_COLD = "Cold";
const ModelType GRADIENT_NIGHT = "Night";
const ModelType GRADIENT_CANDY = "Candy";
const ModelType GRADIENT_GEOGRAPHY = "Geography";
const ModelType GRADIENT_ION = "Ion";
const ModelType GRADIENT_THERMAL = "Thermal";
const ModelType GRADIENT_POLAR = "Polar";
const ModelType GRADIENT_SPECTRUM = "Spectrum";
const ModelType GRADIENT_JET = "Jet";
const ModelType GRADIENT_HUES = "Hues";

const ModelType JOB_RUN_IMMEDIATELY = "Immediately";
const ModelType JOB_RUN_IN_BACKGROUND = "In background";
const ModelType JOB_RUN_SUBMIT_ONLY = "Submit only";
const ModelType JOB_BACKUP = "_backup";

const ModelType SIMULATION_ANALYTICAL = "Analytical";
const ModelType SIMULATION_MONTECARLO = "Monte-Carlo Integration";

const ModelType ALIGNMENT_GENERIC = "Generic";
const ModelType ALIGNMENT_TO_SAMPLE = "Perpendicular to sample x-axis";
const ModelType ALIGNMENT_TO_DIRECT_BEAM = "Perpendicular to direct beam";
const ModelType ALIGNMENT_TO_REFLECTED_BEAM = "Perpendicular to reflected beam";
const ModelType ALIGNMENT_TO_REFLECTED_BEAM_DPOS = "Perpendicular to reflected beam (dpos)";

const ModelType FITPAR_FIXED = "fixed";
const ModelType FITPAR_LIMITED = "limited";
const ModelType FITPAR_LOWERLIMITED = "lower limited";
const ModelType FITPAR_UPPERLIMITED = "upper limited";
const ModelType FITPAR_FREE = "free";

}

#endif // ITEM_CONSTANTS_H
