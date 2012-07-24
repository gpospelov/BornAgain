#include "MaterialManager.h"
#include "Exceptions.h"


/* ************************************************************************* */
// cleaning material database
/* ************************************************************************* */
void MaterialManager::clear() {
    for(materials_t::iterator it = m_materials.begin(); it!= m_materials.end(); it++) {
        if( (*it).second ) delete (*it).second;
    }
    m_materials.clear();
}


/* ************************************************************************* */
// get material
/* ************************************************************************* */
const IMaterial *MaterialManager::getMaterial(const std::string &name)
{
    materials_t::const_iterator pos = m_materials.find(name);
    if( pos != m_materials.end()) {
        return pos->second;
    } else {
        //std::cout << "MaterialManager::Get() -> Info. No such material '" << name << "'." << std::endl;
        return 0;
    }
}


/* ************************************************************************* */
// Create material and add into database. The name of material serve as unique
// identifier. If such material already exists, return it. If such material
// already exist, but its propery are different from users order, throw exception
/* ************************************************************************* */
const IMaterial *MaterialManager::addHomogeneousMaterial(const std::string &name, complex_t refractive_index)
{
    const IMaterial *mat = getMaterial(name);
    if( mat ) {
        //std::cout << "MaterialManager::Add() -> Info. Material '" << name << "' already exists" << std::endl;
        // check if user is trying to create material with same name but different parameters
        const HomogeneousMaterial *old = dynamic_cast<const HomogeneousMaterial *>(mat);
        if(old->getRefractiveIndex() != refractive_index) {
            throw LogicErrorException("MaterialManager::addHomogeneousMaterial() -> Error! Attempt to create material with same name but different refractive index");
        }
        return mat;
    } else {
        IMaterial *hmat = new HomogeneousMaterial(name, refractive_index);
        m_materials[name] = hmat;
        return hmat;
    }
}


/* ************************************************************************* */
// print content of material database on the screen
/* ************************************************************************* */
void MaterialManager::print(std::ostream &ostr) const
{
    ostr << typeid(*this).name() << " " << this << " nmaterials:" << m_materials.size() << std::endl;
    for(materials_t::const_iterator it = m_materials.begin(); it!= m_materials.end(); it++) {
        const IMaterial *mat = (*it).second;
        ostr << *mat << std::endl;
    }
}

