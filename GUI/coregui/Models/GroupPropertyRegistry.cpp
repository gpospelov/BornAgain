// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupPropertyRegistry.cpp
//! @brief     Implements class GroupPropertyRegistry
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupPropertyRegistry.h"

namespace
{

// Correspondance of SessionItem's types to their labels
GroupPropertyRegistry::SelectableGroupMap_t initializeSelectableGroupMap()
{
    GroupPropertyRegistry::SelectableGroupMap_t result;

    std::map<QString, QString> formfactors;
    formfactors[Constants::AnisoPyramidType] = "Aniso Pyramid";
    formfactors[Constants::BoxType] = "Box";
    formfactors[Constants::ConeType] = "Cone";
    formfactors[Constants::Cone6Type] = "Cone6";
    formfactors[Constants::CuboctahedronType] = "Cuboctahedron";
    formfactors[Constants::CylinderType] = "Cylinder";
    formfactors[Constants::DodecahedronType] = "Dodecahedron";
    formfactors[Constants::EllipsoidalCylinderType] = "Ellipsoidal Cylinder";
    formfactors[Constants::FullSphereType] = "Full Sphere";
    formfactors[Constants::FullSpheroidType] = "Full Spheroid";
    formfactors[Constants::HemiEllipsoidType] = "Hemi Ellipsoid";
    formfactors[Constants::IcosahedronType] = "Icosahedron";
    formfactors[Constants::Prism3Type] = "Prism3";
    formfactors[Constants::Prism6Type] = "Prism6";
    formfactors[Constants::PyramidType] = "Pyramid";
    formfactors[Constants::Ripple1Type] = "Ripple1";
    formfactors[Constants::Ripple2Type] = "Ripple2";
    formfactors[Constants::TetrahedronType] = "Tetrahedron";
    formfactors[Constants::TruncatedCubeType] = "Truncated Cube";
    formfactors[Constants::TruncatedSphereType] = "Truncated Sphere";
    formfactors[Constants::TruncatedSpheroidType] = "Truncated Spheroid";
    result[Constants::FormFactorGroup] = formfactors;

    std::map<QString, QString> rotations;
    rotations[Constants::XRotationType] = "X axis Rotation";
    rotations[Constants::YRotationType] = "Y axis Rotation";
    rotations[Constants::ZRotationType] = "Z axis Rotation";
    rotations[Constants::EulerRotationType] = "Euler Rotation";
    result[Constants::RotationGroup] = rotations;

    std::map<QString, QString> roughnesses;
    roughnesses[Constants::LayerBasicRoughnessType] = "Basic";
    roughnesses[Constants::LayerZeroRoughnessType] = "No";
    result[Constants::LayerRoughnessGroup] = roughnesses;

    std::map<QString, QString> detectors;
    detectors[Constants::SphericalDetectorType] = "Spherical detector";
    detectors[Constants::RectangularDetectorType] = "Rectangular detector";
    result[Constants::DetectorGroup] = detectors;

    std::map<QString, QString> distributions;
    distributions[Constants::DistributionGateType] = "Gate distribution";
    distributions[Constants::DistributionLorentzType] = "Lorentz distribution";
    distributions[Constants::DistributionGaussianType] = "Gaussian distribution";
    distributions[Constants::DistributionLogNormalType] = "Log Normal distribution";
    distributions[Constants::DistributionCosineType] = "Cosine distribution";
    result[Constants::DistributionGroup] = distributions;

    std::map<QString, QString> distributions_ext;
    distributions_ext[Constants::DistributionNoneType] = "None";
    distributions_ext[Constants::DistributionGateType] = "Gate";
    distributions_ext[Constants::DistributionLorentzType] = "Lorentz";
    distributions_ext[Constants::DistributionGaussianType] = "Gaussian";
    distributions_ext[Constants::DistributionLogNormalType] = "Log Normal";
    distributions_ext[Constants::DistributionCosineType] = "Cosine";
    result[Constants::DistributionExtendedGroup] = distributions_ext;

    std::map<QString, QString> pdfs_1d;
    pdfs_1d[Constants::FTDistribution1DCauchyType] = "Cauchy 1D";
    pdfs_1d[Constants::FTDistribution1DGaussType] = "Gauss 1D";
    pdfs_1d[Constants::FTDistribution1DGateType] = "Gate 1D";
    pdfs_1d[Constants::FTDistribution1DTriangleType] = "Triangle 1D";
    pdfs_1d[Constants::FTDistribution1DCosineType] = "Cosine 1D";
    pdfs_1d[Constants::FTDistribution1DVoigtType] = "Voigt 1D";
    result[Constants::FTDistribution1DGroup] = pdfs_1d;

    std::map<QString, QString> pdfs_2d;
    pdfs_2d[Constants::FTDistribution2DCauchyType] = "Cauchy 2D";
    pdfs_2d[Constants::FTDistribution2DGaussType] = "Gauss 2D";
    pdfs_2d[Constants::FTDistribution2DGateType] = "Gate 2D";
    pdfs_2d[Constants::FTDistribution2DConeType] = "Cone 2D";
    pdfs_2d[Constants::FTDistribution2DVoigtType] = "Voigt 2D";
    result[Constants::FTDistribution2DGroup] = pdfs_2d;

    std::map<QString, QString> pdecay_1d;
    pdecay_1d[Constants::FTDecayFunction1DCauchyType] = "Cauchy 1D";
    pdecay_1d[Constants::FTDecayFunction1DGaussType] = "Gauss 1D";
    pdecay_1d[Constants::FTDecayFunction1DTriangleType] = "Triangle 1D";
    pdecay_1d[Constants::FTDecayFunction1DVoigtType] = "Voigt 1D";
    result[Constants::FTDecayFunction1DGroup] = pdecay_1d;

    std::map<QString, QString> pdecay_2d;
    pdecay_2d[Constants::FTDecayFunction2DCauchyType] = "Cauchy 2D";
    pdecay_2d[Constants::FTDecayFunction2DGaussType] = "Gauss 2D";
    pdecay_2d[Constants::FTDecayFunction2DVoigtType] = "Voigt 2D";
    result[Constants::FTDecayFunction2DGroup] = pdecay_2d;

    std::map<QString, QString> lattices;
    lattices[Constants::BasicLatticeType] = "Basic";
    lattices[Constants::SquareLatticeType] = "Square";
    lattices[Constants::HexagonalLatticeType] = "Hexagonal";
    result[Constants::LatticeGroup] = lattices;

    std::map<QString, QString> resolution_functions;
    resolution_functions[Constants::ResolutionFunctionNoneType] = "None";
    resolution_functions[Constants::ResolutionFunction2DGaussianType] = "2D Gaussian";
    result[Constants::ResolutionFunctionGroup] = resolution_functions;

    std::map<QString, QString> minimizers;
    minimizers[Constants::MinuitMinimizerType] = "Minuit2";
    minimizers[Constants::GSLMultiMinimizerType] = "GSL MultiMin";
    minimizers[Constants::GeneticMinimizerType] = "TMVA Genetic";
    minimizers[Constants::GSLSimAnMinimizerType] = "GSL Simulated Annealing";
    minimizers[Constants::GSLLMAMinimizerType] = "GSL Levenberg-Marquardt";
    minimizers[Constants::TestMinimizerType] = "Test minimizer";
    result[Constants::MinimizerLibraryGroup] = minimizers;

    std::map<QString, QString> limits;
    limits[Constants::RealLimitsLimitlessType] = "Unlimited";
    limits[Constants::RealLimitsPositiveType] = "Positive";
    limits[Constants::RealLimitsNonnegativeType] = "Nonnegative";
    limits[Constants::RealLimitsLowerLimitedType] = "LowerLimited";
    limits[Constants::RealLimitsUpperLimitedType] = "UpperLimited";
    limits[Constants::RealLimitsLimitedType] = "Limited";
    result[Constants::RealLimitsGroup] = limits;

    return result;
}
}

GroupPropertyRegistry::SelectableGroupMap_t GroupPropertyRegistry::m_selectable_group_map
    = initializeSelectableGroupMap();

bool GroupPropertyRegistry::isValidGroup(const QString &group_type)
{
    auto it = m_selectable_group_map.find(group_type);
    return it==m_selectable_group_map.end() ? false : true;
}

GroupProperty_t
GroupPropertyRegistry::createGroupProperty(const QString &group_name,
                                           const Constants::ModelType &group_type)
{
    Q_ASSERT(isValidGroup(group_type));
    GroupProperty_t result(new GroupProperty(group_name));
    result->setGroupMap(m_selectable_group_map[group_type]);

    return result;
}
