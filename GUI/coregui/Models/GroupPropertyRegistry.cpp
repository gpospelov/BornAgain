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

    // FormFactor items
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

    return result;
}

}


GroupPropertyRegistry::SelectableGroupMap_t GroupPropertyRegistry::m_selectable_group_map = initializeSelectableGroupMap();


FancyGroupProperty *GroupPropertyRegistry::createGroupProperty(const QString &group_name)
{
    if(m_selectable_group_map.contains(group_name)) {
        return createSelectableGroupProperty(group_name);
    }
    else {
        return createFixedGroupProperty(group_name);
    }
}


SelectableGroupProperty *GroupPropertyRegistry::createSelectableGroupProperty(const QString &group_name)
{
    SelectableGroupProperty *result(0);

    if(group_name == Constants::FormFactorGroup) {

        result = new SelectableGroupProperty();

    }
    else {
        throw GUIHelpers::Error("GroupPropertyRegistry::createSelectableGroupProperty() -> Error. Unknown group name"+group_name);
    }

    result->setGroupName(group_name);
    result->setGroupMap(m_selectable_group_map[group_name]);

    return result;
}

FixedGroupProperty *GroupPropertyRegistry::createFixedGroupProperty(const QString &group_name)
{
    FixedGroupProperty *result = new FixedGroupProperty();
    result->setGroupName(group_name);
    return result;
}
