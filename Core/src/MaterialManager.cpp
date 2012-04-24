#include "MaterialManager.h"
#include "Exceptions.h"

MaterialManager *MaterialManager::pInstance = 0;
bool MaterialManager::m_destroyed = false;


MaterialManager::MaterialManager()
{

}


MaterialManager::~MaterialManager()
{
    std::cout << "MaterialManager::~MaterialManager() -> Info. Deleting material manager" << std::endl;
    pInstance = 0;
    m_destroyed = true;

    // clean collection of materials
    clear();
}


/* ************************************************************************* */
// access to material manager
/* ************************************************************************* */
MaterialManager &MaterialManager::instance()
{
    // check if exists, if not, then initialise
    if( !pInstance) {
        // check for dead reference (i.e. object has been initialised but then somebody managed to delete it)
        if( m_destroyed ) {
            onDeadReference();
        } else {
            // first call initalise
            create();
        }
    }
    std::cout << "MaterialManager::Instance() -> Info. Accesing instance... " << pInstance << std::endl;
    return *pInstance;
}


/* ************************************************************************* */
// create single instance of the manager
/* ************************************************************************* */
void MaterialManager::create() {
    std::cout << "MaterialManager::Create() -> Info. Creating material manager" << std::endl;
    static MaterialManager theInstance;
    pInstance = &theInstance;
}


/* ************************************************************************* */
// Action for abnormal situation when object has been occasionally deleted.
// The possibility to rise object again should be still implemented.
/* ************************************************************************* */
void MaterialManager::onDeadReference() {
    throw DeadReferenceException("Dead reference detected.");
}


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
        std::cout << "MaterialManager::Get() -> Info. No such material '" << name << "'." << std::endl;
        return 0;
    }
}


/* ************************************************************************* */
// create material and add into database, but check before if there is no
// such material already. Unikness of material is defined by the material name
/* ************************************************************************* */
const IMaterial *MaterialManager::addHomogeneousMaterial(const std::string &name, complex_t refractive_index)
{
    const IMaterial *mat = getMaterial(name);
    if( mat ) {
        std::cout << "MaterialManager::Add() -> Info. Material '" << name << "' already exists" << std::endl;
        //return dynamic_cast<HomogeneousMaterial *>(mat);
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
void MaterialManager::print() const
{
    std::cout << "=== MaterialManager =========================================" << std::endl;
    for(materials_t::const_iterator it = m_materials.begin(); it!= m_materials.end(); it++) {
        const IMaterial *mat = (*it).second;
        std::cout << *mat << std::endl;
    }
}

