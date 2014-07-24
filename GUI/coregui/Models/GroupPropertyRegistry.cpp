#include "GroupPropertyRegistry.h"
#include "SelectableGroupProperty.h"
#include "FancyGroupProperty.h"
#include "FixedGroupProperty.h"
#include "GUIHelpers.h"
#include "item_constants.h"


namespace {

// Correspondance of ParameterizedItem's types to they labels
GroupPropertyRegistry::SelectableGroupMap_t initializeSelectableGroupMap()
{
    GroupPropertyRegistry::SelectableGroupMap_t result;

    QMap<QString, QString> formfactors;
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
    formfactors[Constants::TruncatedSphereType] = "Truncated Sphere";
    formfactors[Constants::TruncatedSpheroidType] = "Truncated Spheroid";
    result[Constants::FormFactorGroup] = formfactors;

    QMap<QString, QString> roughnesses;
    roughnesses[Constants::LayerBasicRoughnessType] = "Basic";
    roughnesses[Constants::LayerZeroRoughnessType] = "No";
    result[Constants::LayerRoughnessGroup] = roughnesses;

    QMap<QString, QString> detectors;
    detectors[Constants::ThetaPhiDetectorType] = "Theta, Phi plane";
    result[Constants::DetectorGroup] = detectors;

    QMap<QString, QString> pdfs_1d;
    pdfs_1d[Constants::FTDistribution1DCauchyType] = "Cauchy 1D";
    pdfs_1d[Constants::FTDistribution1DGaussType] = "Gauss 1D";
    pdfs_1d[Constants::FTDistribution1DGateType] = "Gate 1D";
    pdfs_1d[Constants::FTDistribution1DTriangleType] = "Triangle 1D";
    pdfs_1d[Constants::FTDistribution1DCosineType] = "Cosine 1D";
    pdfs_1d[Constants::FTDistribution1DVoigtType] = "Voigt 1D";
    result[Constants::FTDistribution1DGroup] = pdfs_1d;

    QMap<QString, QString> pdfs_2d;
    pdfs_2d[Constants::FTDistribution2DCauchyType] = "Cauchy 2D";
    pdfs_2d[Constants::FTDistribution2DGaussType] = "Gauss 2D";
    pdfs_2d[Constants::FTDistribution2DGateType] = "Gate 2D";
    pdfs_2d[Constants::FTDistribution2DConeType] = "Cone 2D";
    pdfs_2d[Constants::FTDistribution2DVoigtType] = "Voigt 2D";
    result[Constants::FTDistribution2DGroup] = pdfs_2d;

    QMap<QString, QString> lattices;
    lattices[Constants::BasicLatticeType] = "Basic";
    lattices[Constants::SquareLatticeType] = "Square";
    lattices[Constants::HexagonalLatticeType] = "Hexagonal";
    result[Constants::LatticeGroup] = lattices;

//    QMap<QString, QString> materials;
//    lattices[Constants::HomogeneousMaterialType] = "Homogeneous Material";
//    lattices[Constants::HomogeneousMagneticMaterialType] = "Homogeneous Magnetic Material";
//    result[Constants::MaterialGroup] = materials;

    return result;
}

}


GroupPropertyRegistry::SelectableGroupMap_t GroupPropertyRegistry::m_selectable_group_map = initializeSelectableGroupMap();


FancyGroupProperty *GroupPropertyRegistry::createGroupProperty(const QString &group_name, const Constants::ModelType &group_model)
{
    Constants::ModelType groupModelType = group_model;
    if(groupModelType.isEmpty()) groupModelType = group_name;

    FancyGroupProperty *result = new FancyGroupProperty(group_name);

    if(m_selectable_group_map.contains(groupModelType)) {
        result->setGroupType(FancyGroupProperty::SelectableGroupType);
        result->setGroupMap(m_selectable_group_map[groupModelType]);
    }
    else {
        result->setGroupType(FancyGroupProperty::FixedGroupType);
        //result->setValue(group_n);
        QMap<QString, QString> group_map;
        group_map[groupModelType] = "No label";
        result->setGroupMap(group_map);
    }

    return result;
}


//SelectableGroupProperty *GroupPropertyRegistry::createSelectableGroupProperty(const QString &group_name)
//{
//    if( !m_selectable_group_map.contains(group_name) )
//        return 0;

//    SelectableGroupProperty *result = new SelectableGroupProperty(group_name);
//    result->setGroupMap(m_selectable_group_map[group_name]);
//    return result;
//}

//FixedGroupProperty *GroupPropertyRegistry::createFixedGroupProperty(const QString &group_name)
//{
//    FixedGroupProperty *result = new FixedGroupProperty(group_name);
//    QMap<QString, QString> group_map;
//    group_map[group_name] = "No label";
//    result->setGroupMap(group_map[group_name]);
//    return result;
//}



