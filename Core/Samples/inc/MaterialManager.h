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

#include <iostream>
#include <string>
#include <map>
#include "Exceptions.h"
#include "ISingleton.h"
#include "HomogeneousMaterial.h"

//! Manager of materials used in simulation.

//! A singleton that maintains a database of materials, and
//! provides a common and unique interface for material creation and access.
//!
class MaterialManager: public ISingleton<MaterialManager>
{
 public:
    virtual ~MaterialManager() { clear(); }

    //! Return material from database.
    static const IMaterial *getMaterial(const std::string &name)
    { return instance().this_getMaterial(name); }

    //! Add material to database.
    static const IMaterial *getHomogeneousMaterial(
        const std::string &name, const complex_t &refractive_index)
    { return instance().this_getHomogeneousMaterial(name, refractive_index); }

    //! Add material to database.
    static const IMaterial *getHomogeneousMaterial(
        const std::string &name,
        double refractive_index_real,
        double refractive_index_imag)
    { return instance().this_getHomogeneousMaterial(
            name, refractive_index_real, refractive_index_imag); }

    //! Wrap print.
    friend std::ostream &operator<<(
        std::ostream &ostr, const MaterialManager &m)
    { m.print(ostr); return ostr; }

 protected:
    MaterialManager(){}
    friend class ISingleton<MaterialManager >;

    //! Clear database.
    void clear();

    //! Dump this to stream.
    virtual void print(std::ostream &ostr) const;

    std::map<std::string, IMaterial*> m_materials; //!< our database
 private:
    const IMaterial *this_getMaterial(const std::string &name);
    const IMaterial *this_getHomogeneousMaterial(
        const std::string &name, const complex_t &refractive_index);
    const IMaterial *this_getHomogeneousMaterial(
        const std::string &name,
        double refractive_index_real, double refractive_index_imag);
    void check_refractive_index(const complex_t &index);
};

#endif /* MATERIALMANAGER_H */
