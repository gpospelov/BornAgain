// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/MaterialManager.cpp
//! @brief     Implements class MaterialManager.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialManager.h"

#include "HomogeneousMagneticMaterial.h"
#include "Exceptions.h"
#include "MessageService.h"
#include "Macros.h"
GCC_DIAG_OFF(strict-aliasing);
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing);

//! Materials database type.

typedef std::map<std::string, IMaterial*> materials_t;

//! Clear database.

void MaterialManager::clear() {
    static boost::mutex single_mutex;
    boost::unique_lock<boost::mutex> single_lock( single_mutex );
    for(materials_t::iterator
            it = m_materials.begin(); it!= m_materials.end(); ++it) {
        if( (*it).second )
            delete (*it).second;
    }
    m_materials.clear();
}

//! Returns material.

const IMaterial *MaterialManager::this_getMaterial(const std::string& name)
{
    static boost::mutex single_mutex;
    boost::unique_lock<boost::mutex> single_lock( single_mutex );
    materials_t::const_iterator pos = m_materials.find(name);
    if( pos != m_materials.end()) {
        return pos->second;
    } else {
        return 0;
    }
}

//! Creates material, and add into database using name of material as identifier.

const IMaterial *MaterialManager::this_getHomogeneousMaterial(
    const std::string& name, const complex_t& refractive_index)
{
    check_refractive_index(refractive_index);

    static boost::mutex single_mutex;
    boost::unique_lock<boost::mutex> single_lock( single_mutex );
    const IMaterial *mat = getMaterial(name);
    if( mat ) {
        // check if user is trying to create material
        // with same name but different parameters
        if(!mat->isScalarMaterial()) {
            throw LogicErrorException("MaterialManager::this_getHomogeneousMaterial() -> Attempt to make existing magnetic material non-magnetic one. Material name '"+mat->getName()+"'.");
        }
        const HomogeneousMaterial *old =
            dynamic_cast<const HomogeneousMaterial *>(mat);
        if(old->getRefractiveIndex() != refractive_index) {
            HomogeneousMaterial *non_const_mat =
                const_cast<HomogeneousMaterial *>(old);
            non_const_mat->setRefractiveIndex(refractive_index);
            msglog(MSG::WARNING) << "MaterialManager::addHomogeneousMaterial()" <<
                "-> Redefining refractive index for material '" << name << "'";
        }
        return mat;
    } else {
        IMaterial *hmat = new HomogeneousMaterial(name, refractive_index);
        m_materials[name] = hmat;
        return hmat;
    }
}

//! Creates material, and add into database using name of material as identifier.

const IMaterial *MaterialManager::this_getHomogeneousMaterial(
    const std::string& name,
    double refractive_index_delta,
    double refractive_index_beta)
{
    return this_getHomogeneousMaterial(
        name, complex_t(1.0-refractive_index_delta, refractive_index_beta));
}

//! Creates magnetic material, and add into database using name of material
//! as identifier.

const IMaterial* MaterialManager::this_getHomogeneousMagneticMaterial(
        const std::string& name, const complex_t& refractive_index,
        const kvector_t& magnetic_field)
{
    check_refractive_index(refractive_index);

    static boost::mutex single_mutex;
    boost::unique_lock<boost::mutex> single_lock( single_mutex );
    const IMaterial *mat = getMaterial(name);
    if( mat ) {
        // check if user is trying to create material
        // with same name but different parameters
        if(mat->isScalarMaterial()) {
            throw LogicErrorException("MaterialManager::this_getHomogeneousMagneticMaterial() -> Attempt to make existing non-magnetic material magnetic one. Material name '"+mat->getName()+"'.");
        }

        const HomogeneousMagneticMaterial *mold =
            dynamic_cast<const HomogeneousMagneticMaterial *>(mat);

        if(mold->getMagneticField() != magnetic_field) {
            HomogeneousMagneticMaterial *non_const_mat =
                const_cast<HomogeneousMagneticMaterial *>(mold);
            non_const_mat->setMagneticField(magnetic_field);
            msglog(MSG::WARNING) <<
                "MaterialManager::addHomogeneousMagneticMaterial()" <<
                "-> Redefining magnetic field for material '" << name << "'";
        }
        if(mold->getRefractiveIndex() != refractive_index) {
            HomogeneousMagneticMaterial *non_const_mat =
                const_cast<HomogeneousMagneticMaterial *>(mold);
            non_const_mat->setRefractiveIndex(refractive_index);
            msglog(MSG::WARNING) <<
                "MaterialManager::addHomogeneousMagneticMaterial()" <<
                "-> Redefining refractive index for material '" << name << "'";
        }

        return mat;
    } else {
        IMaterial *hmat = new HomogeneousMagneticMaterial(name,
                refractive_index, magnetic_field);
        m_materials[name] = hmat;
        return hmat;
    }
}

//! Creates magnetic material, and add into database using name of material
//! as identifier.

const IMaterial* MaterialManager::this_getHomogeneousMagneticMaterial(
        const std::string& name, double refractive_index_delta,
        double refractive_index_beta, const kvector_t& magnetic_field)
{
    return this_getHomogeneousMagneticMaterial(
        name, complex_t(1.0-refractive_index_delta, refractive_index_beta),
        magnetic_field);
}

const IMaterial* MaterialManager::this_getInvertedMaterial(
        const std::string& name)
{
    const IMaterial *p_orig_material = getMaterial(name);
    if (!p_orig_material) return 0;
    const HomogeneousMagneticMaterial *p_magn_material =
            dynamic_cast<const HomogeneousMagneticMaterial *>(p_orig_material);
    if (!p_magn_material) return p_orig_material;
    std::string new_name = name + "_inv";
    return this_getHomogeneousMagneticMaterial(new_name,
            p_magn_material->getRefractiveIndex(),
            -p_magn_material->getMagneticField());
}

//! Dump this to stream.
void MaterialManager::print(std::ostream& ostr) const
{
    ostr << typeid(*this).name() << " " << this <<
        " nmaterials:" << m_materials.size() << std::endl;
    for(materials_t::const_iterator
            it = m_materials.begin(); it!= m_materials.end(); ++it) {
        const IMaterial *mat = (*it).second;
        ostr << *mat << std::endl;
    }
}

//! Checks refractive index for consistency
// FIXME what are allowed values for refractive index ?
void MaterialManager::check_refractive_index(const complex_t &index)
{
    bool isConsistent(true);
    if( (index.imag() == 0.0) && (index.real() == 0.0) ) isConsistent = false;
    if( (index.imag() < 0.0) || (index.real() < 0.0) ) isConsistent = false;
    if( (index.imag() > 1.0) || (index.real() > 1.0) ) isConsistent = false;
    if( (index.imag() == 1.0) ) isConsistent = false;

    if( !isConsistent ) {
        msglog(MSG::ERROR) << "MaterialManager::check_refractive_index() -> "
                           << "Suspicious refractive index " << index;
    }
}


//! set new material name
bool MaterialManager::setMaterialName(const std::string &old_name, const std::string &new_name)
{
    std::cout << "MaterialManager::setMaterialName() -> " << std::endl;
    if( !getMaterial(old_name) )  {
        msglog(MSG::ERROR) << "MaterialManager::setMaterialName() -> "
                           << "No material with name " << old_name;
        return false;
    }

    if( getMaterial(new_name) )  {
        msglog(MSG::ERROR) << "MaterialManager::setMaterialName() -> "
                           << "Existingh name " << new_name;
        return false;
    }

    IMaterial *mat = m_materials[old_name];
    mat->setName(new_name);
    m_materials.erase(old_name);
    m_materials[new_name] = mat;
    return true;
}


bool MaterialManager::deleteMaterial(const std::string &name)
{
    std::cout << "MaterialManager::deleteMaterial() -> " << std::endl;
    if( !getMaterial(name) )  {
        msglog(MSG::ERROR) << "MaterialManager::deleteMaterial() -> "
                           << "No material with name " << name;
        return false;
    }

    delete m_materials[name];
    m_materials.erase(name);
    return true;
}


bool MaterialManager::setMaterialRefractiveIndex(const std::string &name, const complex_t &index)
{
    std::cout << "MaterialManager::setMaterialRefractiveIndex() -> " << std::endl;
    if( !getMaterial(name) )  {
        msglog(MSG::ERROR) << "MaterialManager::setMaterialRefractiveIndex() -> "
                           << "No material with name " << name;
        return false;
    }

    HomogeneousMaterial *mat = dynamic_cast<HomogeneousMaterial *>(m_materials[name]);
    if( !mat ) {
        msglog(MSG::ERROR) << "MaterialManager::setMaterialRefractiveIndex() -> "
                           << "can't cast to HomogeneousMaterial' " << name;
        return false;
    }
    mat->setRefractiveIndex(index);
    return true;
}

