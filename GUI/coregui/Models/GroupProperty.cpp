#include "GroupProperty.h"
#include "FormFactorItems.h"
#include "ParticleItem.h"
#include "DetectorItems.h"
#include "FTDistributionItems.h"
#include "LatticeTypeItems.h"
#include "ParaCrystalItems.h"
#include "LayerRoughnessItems.h"

namespace {
template<typename T> ParameterizedItem *createInstance() { return new T; }

GroupProperty::GroupMap_t initializeFormFactorMap() {
    GroupProperty::GroupMap_t result;

    QMap<QString, ParameterizedItem *(*)()> formfactors;
    formfactors[Constants::AnisoPyramidType] = &createInstance<AnisoPyramidItem>;
    formfactors[Constants::BoxType] = &createInstance<BoxItem>;
    formfactors[Constants::ConeType] = &createInstance<ConeItem>;
    formfactors[Constants::Cone6Type] = &createInstance<Cone6Item>;
    formfactors[Constants::CuboctahedronType] = &createInstance<CuboctahedronItem>;
    formfactors[Constants::CylinderType] = &createInstance<CylinderItem>;
    formfactors[Constants::EllipsoidalCylinderType] = &createInstance<EllipsoidalCylinderItem>;
    formfactors[Constants::FullSphereType] = &createInstance<FullSphereItem>;
    formfactors[Constants::FullSpheroidType] = &createInstance<FullSpheroidItem>;
    formfactors[Constants::HemiEllipsoidType] = &createInstance<HemiEllipsoidItem>;
    formfactors[Constants::Prism3Type] = &createInstance<Prism3Item>;
    formfactors[Constants::Prism6Type] = &createInstance<Prism6Item>;
    formfactors[Constants::PyramidType] = &createInstance<PyramidItem>;
    formfactors[Constants::Ripple1Type] = &createInstance<Ripple1Item>;
    formfactors[Constants::Ripple2Type] = &createInstance<Ripple2Item>;
    formfactors[Constants::TetrahedronType] = &createInstance<TetrahedronItem>;
    formfactors[Constants::TruncatedSphereType] = &createInstance<TruncatedSphereItem>;
    formfactors[Constants::TruncatedSpheroidType] = &createInstance<TruncatedSpheroidItem>;
    result["Form Factor"] = formfactors;

    QMap<QString, ParameterizedItem *(*)()> ft_distributions_1d;
    ft_distributions_1d[QString("Cauchy 1D")] = &createInstance<FTDistribution1DCauchyItem>;
    ft_distributions_1d[QString("Gauss 1D")] = &createInstance<FTDistribution1DGaussItem>;
    ft_distributions_1d[QString("Gate 1D")] = &createInstance<FTDistribution1DGateItem>;
    ft_distributions_1d[QString("Triangle 1D")] = &createInstance<FTDistribution1DTriangleItem>;
    ft_distributions_1d[QString("Cosine 1D")] = &createInstance<FTDistribution1DCosineItem>;
    ft_distributions_1d[QString("Voigt 1D")] = &createInstance<FTDistribution1DVoigtItem>;
    result["PDF"] = ft_distributions_1d;

    QMap<QString, ParameterizedItem *(*)()> ft_distributions_2d;
    ft_distributions_2d[QString("Cauchy 2D")] = &createInstance<FTDistribution2DCauchyItem>;
    ft_distributions_2d[QString("Gauss 2D")] = &createInstance<FTDistribution2DGaussItem>;
    ft_distributions_2d[QString("Gate 2D")] = &createInstance<FTDistribution2DGateItem>;
    ft_distributions_2d[QString("Cone 2D")] = &createInstance<FTDistribution2DConeItem>;
    ft_distributions_2d[QString("Voigt 2D")] = &createInstance<FTDistribution2DVoigtItem>;
    result["PDF #1"] = ft_distributions_2d;
    result["PDF #2"] = ft_distributions_2d;

    QMap<QString, ParameterizedItem *(*)()> lattice_types;
    lattice_types[QString("Basic")] = &createInstance<BasicLatticeTypeItem>;
    lattice_types[QString("Square")] = &createInstance<SquareLatticeTypeItem>;
    lattice_types[QString("Hexagonal")] = &createInstance<HexagonalLatticeTypeItem>;
    result["Lattice_type"] = lattice_types;

    QMap<QString, ParameterizedItem *(*)()> detector_types;
    //detector_types[XYDetectorItem::P_MODEL_TYPE] = &createInstance<XYDetectorItem>;
    detector_types["Theta, Phi plane"] = &createInstance<ThetaPhiDetectorItem>;
    result["Detector type"] = detector_types;

    QMap<QString, ParameterizedItem *(*)()> roughnesses;
    roughnesses[QString("No")] = &createInstance<LayerZeroRoughnessItem>;
    roughnesses[QString("Basic")] = &createInstance<LayerRoughnessItem>;
    result["Top roughness"] = roughnesses;


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

int GroupProperty::toIndex(const QString &value) const
{
    QStringList name_list = getValues();
    for (int i = 0; i < name_list.size(); ++i) {
        if (value == name_list[i]) {
            return i;
        }
    }
    return -1;
}

QString GroupProperty::toString(int index) const
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
