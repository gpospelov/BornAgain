#include "Material.h"
#include "BaseMaterialImpl.h"
#include "WavevectorInfo.h"
#include "Transform3D.h"
#include <typeinfo>

Material::Material(const Material& material)
    : m_material_impl(material.m_material_impl->clone())
{}

Material::Material(std::unique_ptr<BaseMaterialImpl> material_impl)
    : m_material_impl(std::move(material_impl))
{}

Material Material::inverted() const
{
    std::unique_ptr<BaseMaterialImpl> material_impl(m_material_impl->inverted());
    return Material(std::move(material_impl));
}

complex_t Material::refractiveIndex(double wavelength) const
{
    return m_material_impl->refractiveIndex(wavelength);
}

complex_t Material::refractiveIndex2(double wavelength) const
{
    return m_material_impl->refractiveIndex2(wavelength);
}

bool Material::isScalarMaterial() const
{
    return m_material_impl->isScalarMaterial();
}

std::string Material::getName() const
{
    return m_material_impl->getName();
}

size_t Material::dataType() const
{
    //TODO: reimplement using CRTP or just static type identifiers in material implementations
    return typeid(*m_material_impl).hash_code();
}

kvector_t Material::magnetization() const
{
    return m_material_impl->magnetization();
}

complex_t Material::materialData() const
{
    return m_material_impl->materialData();
}

complex_t Material::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    return m_material_impl->scalarSubtrSLD(wavevectors);
}

Eigen::Matrix2cd Material::polarizedSubtrSLD(const WavevectorInfo& wavevectors) const
{
    return m_material_impl->polarizedSubtrSLD(wavevectors);
}

Material Material::transformedMaterial(const Transform3D& transform) const
{
    std::unique_ptr<BaseMaterialImpl> material_impl(m_material_impl->transformedMaterial(transform));
    return Material(std::move(material_impl));
}

std::ostream& operator<<(std::ostream& ostr, const Material& m)
{
    m.m_material_impl->print(ostr);
    return ostr;
}

bool operator==(const Material& left, const Material& right)
{
    if (left.getName() != right.getName()) return false;
    if (left.magnetization() != right.magnetization()) return false;
    if (left.materialData() != right.materialData()) return false;
    if (left.dataType() != right.dataType()) return false;
    return true;
}

