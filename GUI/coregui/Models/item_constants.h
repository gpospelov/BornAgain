#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <QString>

namespace Constants {

// --- Items -------------------------------------------------------------------

const QString LayerType = "Layer";
const QString MultiLayerType = "MultiLayer";
const QString ParticleType = "Particle";
const QString ParticleLayoutType = "ParticleLayout";
const QString ParticleCoreShellType = "ParticleCoreShell";
const QString InterferenceFunction1DParaCrystalType = "InterferenceFunction1DParaCrystal";
const QString InterferenceFunction2DParaCrystalType = "InterferenceFunction2DParaCrystal";
const QString InstrumentType = "Instrument";
const QString DetectorType = "Detector";
const QString BeamType = "Beam";

const QString FormFactorType = "FormFactor";
const QString AnisoPyramidType = "AnisoPyramid";
const QString BoxType = "Box";
const QString ConeType = "Cone";
const QString Cone6Type = "Cone6";
const QString CuboctahedronType = "Cuboctahedron";
const QString CylinderType = "Cylinder";
const QString EllipsoidalCylinderType = "EllipsoidalCylinder";
const QString FullSphereType = "FullSphere";
const QString FullSpheroidType = "FullSpheroid";
const QString HemiEllipsoidType = "HemiEllipsoid";
const QString Prism3Type = "Prism3";
const QString Prism6Type = "Prism6";
const QString PyramidType = "Pyramid";
const QString Ripple1Type = "Ripple1";
const QString Ripple2Type = "Ripple2";
const QString TetrahedronType = "Tetrahedron";
const QString TruncatedSphereType = "TruncatedSphere";
const QString TruncatedSpheroidType = "TruncatedSpheroid";

const QString VectorType = "Vector";

const QString LayerRoughnessType = "LayerRoughness";
const QString LayerZeroRoughnessType = "LayerZeroRoughness";

const QString ThetaPhiDetectorType = "ThetaPhiDetector";

const QString FTDistribution1DCauchyType = "FTDistribution1DCauchy";
const QString FTDistribution1DGaussType = "FTDistribution1DGauss";
const QString FTDistribution1DGateType = "FTDistribution1DGate";
const QString FTDistribution1DTriangleType = "FTDistribution1DTriangle";
const QString FTDistribution1DCosineType = "FTDistribution1DCosine";
const QString FTDistribution1DVoigtType = "FTDistribution1DVoigt";

const QString FTDistribution2DCauchyType = "FTDistribution2DCauchy";
const QString FTDistribution2DGaussType = "FTDistribution2DGauss";
const QString FTDistribution2DGateType = "FTDistribution2DGate";
const QString FTDistribution2DConeType = "FTDistribution2DCone";
const QString FTDistribution2DVoigtType = "FTDistribution2DVoigt";

const QString BasicLatticeType = "BasicLatticeType";
const QString SquareLatticeType = "SquareLatticeType";
const QString HexagonalLatticeType = "HexagonalLatticeType";


// --- Groups ------------------------------------------------------------------

const QString FormFactorGroup = "Form Factor";
const QString LayerRoughnessGroup = "Roughness";
const QString DetectorGroup = "Detector group";
const QString FTDistribution1DGroup = "PDF 1D";
const QString FTDistribution2DGroupA = "PDF 2D #1";
const QString FTDistribution2DGroupB = "PDF 2D #2";
const QString LatticeGroup = "Lattice_type";


}


#endif
