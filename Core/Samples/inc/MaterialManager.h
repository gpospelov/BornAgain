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
#include "IMaterial.h"
#include "ISingleton.h"
#include "HomogeneousMaterial.h"

//! Manager of materials used in simulation.

//! It is a singleton which provides common and unique interface for
//! material creation and access. No thread safety.
//!
class MaterialManager: public ISingleton<MaterialManager>
{
  public:
    virtual ~MaterialManager() { clear(); }

    //! access material by name
    const IMaterial *getMaterial(const std::string &name);

    //! add one material to the database
    const IMaterial *addHomogeneousMaterial(
        const std::string &name, const complex_t &refractive_index);
    //! add one material to the database
    const IMaterial *addHomogeneousMaterial(
        const std::string& name,
        double refractive_index_real,
        double refractive_index_imag);

    //! clear the material database
    void clear();

    //! print material class
    friend std::ostream &operator<<(
        std::ostream &ostr, const MaterialManager &m)
    { m.print(ostr); return ostr; }

  protected:
    MaterialManager(){}
    friend class ISingleton<MaterialManager >;

    //! print material class
    virtual void print(std::ostream &ostr) const;

    std::map<std::string, IMaterial*> m_materials; //!< our database
};

#endif // MATERIALMANAGER_H
