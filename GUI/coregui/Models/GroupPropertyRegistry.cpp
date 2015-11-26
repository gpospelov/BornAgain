// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GroupPropertyRegistry.cpp
//! @brief     Implements class GroupPropertyRegistry
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GroupPropertyRegistry.h"
#include "GroupProperty.h"
#include "GUIHelpers.h"
#include "item_constants.h"
#include <QDebug>

namespace
{

// Correspondance of ParameterizedItem's types to their labels
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
    formfactors[Constants::EllipsoidalCylinderType] = "Ellipsoidal Cylinder";
    formfactors[Constants::FullSphereType] = "Full Sphere";
    formfactors[Constants::FullSpheroidType] = "Full Spheroid";
    formfactors[Constants::HemiEllipsoidType] = "Hemi Ellipsoid";
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
    detectors[Constants::SphericalDetectorType] = "[Phi, Alpha] plane";
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

    std::map<QString, QString> lattices;
    lattices[Constants::BasicLatticeType] = "Basic";
    lattices[Constants::SquareLatticeType] = "Square";
    lattices[Constants::HexagonalLatticeType] = "Hexagonal";
    result[Constants::LatticeGroup] = lattices;

    std::map<QString, QString> resolution_functions;
    resolution_functions[Constants::ResolutionFunctionNoneType] = "None";
    resolution_functions[Constants::ResolutionFunction2DGaussianType] = "2D Gaussian";
    result[Constants::ResolutionFunctionGroup] = resolution_functions;

    return result;
}
}

GroupPropertyRegistry::SelectableGroupMap_t GroupPropertyRegistry::m_selectable_group_map
    = initializeSelectableGroupMap();

GroupProperty_t
GroupPropertyRegistry::createGroupProperty(const QString &group_name,
                                           const Constants::ModelType &group_model)
{
    Constants::ModelType groupModelType = group_model;
    if (groupModelType.isEmpty())
        groupModelType = group_name;

    GroupProperty_t result(new GroupProperty(group_name));

    if (m_selectable_group_map.find(groupModelType) != m_selectable_group_map.end()) {
        qDebug() << "GroupPropertyRegistry::createGroupProperty() -> creating selectable group of "
                    "groupModelType" << groupModelType;
        result->setGroupType(GroupProperty::SELECTABLE);
        result->setGroupMap(m_selectable_group_map[groupModelType]);
    } else {
        result->setGroupType(GroupProperty::FIXED);
        // result->setValue(group_n);
        std::map<QString, QString> group_map;
        group_map[groupModelType] = "No label";
        result->setGroupMap(group_map);
    }

    return result;
}
