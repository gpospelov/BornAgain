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
#include "Exceptions.h"

//! our database is a map: name -> pointer to material
typedef std::map<std::string, IMaterial*> materials_t;

//! clear the material database

void MaterialManager::clear() {
    for(materials_t::iterator it = m_materials.begin(); it!= m_materials.end(); ++it) {
        if( (*it).second ) delete (*it).second;
    }
    m_materials.clear();
}

//! access material by name

const IMaterial* MaterialManager::getMaterial(const std::string &name)
{
    materials_t::const_iterator pos = m_materials.find(name);
    if( pos != m_materials.end()) {
        return pos->second;
    } else {
        return 0;
    }
}

//! Add one material to the database.

//! The material name serves as unique identifier.
//! If name is already in use, return material, but only if properties are
//! the same as given here; otherwise throw exception.
//!    @TODO: This behaviour has changed!
//! If name is new, register the material. 
//!
const IMaterial* MaterialManager::addHomogeneousMaterial(
    const std::string& name, const complex_t& refractive_index)
{
    const IMaterial *mat = getMaterial(name);
    if( mat ) {
        // check if user is trying to create material with same name but different parameters
        const HomogeneousMaterial *old =
            dynamic_cast<const HomogeneousMaterial *>(mat);
        if(old->getRefractiveIndex() != refractive_index) {
            HomogeneousMaterial *non_const_mat =
                const_cast<HomogeneousMaterial *>(old);
            non_const_mat->setRefractiveIndex(refractive_index);
//            throw LogicErrorException("MaterialManager::addHomogeneousMaterial() -> Error! Attempt to create material with same name but different refractive index");
        }
        return mat;
    } else {
        IMaterial *hmat = new HomogeneousMaterial(name, refractive_index);
        m_materials[name] = hmat;
        return hmat;
    }
}

//! Add one material to the database.

const IMaterial* MaterialManager::addHomogeneousMaterial(
    const std::string& name,
    double refractive_index_real,
    double refractive_index_imag) 
{
    return addHomogeneousMaterial(
        name, complex_t(refractive_index_real, refractive_index_imag));
}

//! Dump entire data base to stream.

void MaterialManager::print(std::ostream &ostr) const
{
    ostr << typeid(*this).name() << " " << this << " nmaterials:" << m_materials.size() << std::endl;
    for(materials_t::const_iterator it = m_materials.begin(); it!= m_materials.end(); ++it) {
        const IMaterial *mat = (*it).second;
        ostr << *mat << std::endl;
    }
}
