// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/MaterialManager.h
//! @brief     Defines class MaterialManager.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "WinDllMacros.h"
#include "Exceptions.h"
#include "ISingleton.h"
#include "HomogeneousMaterial.h"
#include <iostream>
#include <string>
#include <map>

//! Manager of materials used in simulation.

//! A singleton that maintains a database of materials, and
//! provides a common and unique interface for material creation and access.
//!
class BA_CORE_API_ MaterialManager: public ISingleton<MaterialManager>
{
 public:
    typedef std::map<std::string, IMaterial*> materials_t;
    typedef materials_t::iterator iterator;
    typedef materials_t::const_iterator const_iterator;

    virtual ~MaterialManager() { clear(); }

    //! Returns material from database.
    static const IMaterial *getMaterial(const std::string& name)
    { return instance().this_getMaterial(name); }

    //! Adds material to database.
    static const IMaterial *getHomogeneousMaterial(
        const std::string& name, const complex_t& refractive_index)
    { return instance().this_getHomogeneousMaterial(name, refractive_index); }

    //! Adds material to database.
    static const IMaterial *getHomogeneousMaterial(
        const std::string& name,
        double refractive_index_delta,
        double refractive_index_beta)
    { return instance().this_getHomogeneousMaterial(
            name, refractive_index_delta, refractive_index_beta); }

    //! returns number of materials
    static int getNumberOfMaterials() { return instance().this_getNumberOfMaterials(); }

    //! Sends class description to stream.
    friend std::ostream& operator<<(
        std::ostream& ostr, const MaterialManager& m)
    { m.print(ostr); return ostr; }

    //! access to container begin
    iterator begin() { return m_materials.begin(); }

    //! access to container begin
    iterator end() { return m_materials.end(); }

    //! set new material name
    bool setMaterialName(const std::string &old_name, const std::string &new_name);

    //! set new material refractive index
    bool setMaterialRefractiveIndex(const std::string &name, const complex_t &index);

    //! delete material
    bool deleteMaterial(const std::string &name);

 protected:
    MaterialManager(){}
    friend class ISingleton<MaterialManager >;

    //! Clear database.
    void clear();

    //! Dump this to stream.
    virtual void print(std::ostream& ostr) const;

    materials_t m_materials; //!< our database

 private:
    const IMaterial *this_getMaterial(const std::string& name);
    const IMaterial *this_getHomogeneousMaterial(
        const std::string& name, const complex_t& refractive_index);
    const IMaterial *this_getHomogeneousMaterial(
        const std::string& name,
        double refractive_index_delta, double refractive_index_beta);
    int this_getNumberOfMaterials() const { return (int)m_materials.size(); }

    void check_refractive_index(const complex_t &index);
};

#endif /* MATERIALMANAGER_H */


