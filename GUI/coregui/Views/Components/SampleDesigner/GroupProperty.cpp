#include "GroupProperty.h"
#include "FormFactorItems.h"

namespace {
template<typename T> ParameterizedItem *createInstance() { return new T; }

GroupProperty::GroupMap_t initializeFormFactorMap() {
    GroupProperty::GroupMap_t result;

    QMap<QString, ParameterizedItem *(*)()> formfactors;
    formfactors[QString("AnisoPyramid")] = &createInstance<AnisoPyramidItem>;
    formfactors[QString("Box")] = &createInstance<BoxItem>;
    formfactors[QString("Cone")] = &createInstance<ConeItem>;
    formfactors[QString("Cone6")] = &createInstance<Cone6Item>;
    formfactors[QString("Cuboctahedron")] = &createInstance<CuboctahedronItem>;
    formfactors[QString("Cylinder")] = &createInstance<CylinderItem>;
    formfactors[QString("EllipsoidalCylinder")] = &createInstance<EllipsoidalCylinderItem>;
    formfactors[QString("FullSphere")] = &createInstance<FullSphereItem>;
    formfactors[QString("FullSpheroid")] = &createInstance<FullSpheroidItem>;
    formfactors[QString("HemiEllipsoid")] = &createInstance<HemiEllipsoidItem>;
    formfactors[QString("Prism3")] = &createInstance<Prism3Item>;
    formfactors[QString("Prism6")] = &createInstance<Prism6Item>;
    formfactors[QString("Pyramid")] = &createInstance<PyramidItem>;
    formfactors[QString("Ripple1")] = &createInstance<Ripple1Item>;
    formfactors[QString("Ripple2")] = &createInstance<Ripple2Item>;
    formfactors[QString("Tetrahedron")] = &createInstance<TetrahedronItem>;
    formfactors[QString("TruncatedSphere")] = &createInstance<TruncatedSphereItem>;
    formfactors[QString("TruncatedSpheroid")] = &createInstance<TruncatedSpheroidItem>;
    result["Form Factor"] = formfactors;
    return result;
}
}


GroupProperty::GroupMap_t GroupProperty::m_group_map =
        initializeFormFactorMap();

GroupProperty::GroupProperty(QString group_name, QString value)
    : m_value("Undefined")
    , m_group_name("Undefined")
{
    if (m_group_map.contains(group_name)) {
        m_group_name = group_name;
        if (m_group_map[m_group_name].contains(value)) {
            m_value = value;
        }
    }

}

int GroupProperty::index() const
{
    return toIndex(m_value);
}

int GroupProperty::toIndex(const QString value) const
{
    QStringList name_list = getValues();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString GroupProperty::toString(const int index) const
{
    QStringList name_list = getValues();
    if (index<0 || index>=name_list.size()) {
        return QString();
    }
    return name_list[index];
}

ParameterizedItem *GroupProperty::createCorrespondingItem(QString name)
{
    Q_ASSERT(isDefined());
    if (!m_group_map[m_group_name].contains(name)) return 0;
    return m_group_map[m_group_name][name]();
}
