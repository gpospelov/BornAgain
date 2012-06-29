#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MaterialManager.h
//! @brief  Definition of MaterialManager class
//! @author Scientific Computing Group at FRM II
//! @date   20.04.2012

#include <iostream>
#include <string>
#include <map>
#include "Exceptions.h"
#include "IMaterial.h"
#include "ISingleton.h"
#include "HomogeneousMaterial.h"


//- -------------------------------------------------------------------
//! @class MaterialManager
//! @brief Manager of materials used in simulatiom.
//!
//! It is a singleton which provides common and unique interface for
//! material creation and access. No thread safety.
//- -------------------------------------------------------------------
class MaterialManager: public ISingleton<MaterialManager>
{
public:
    //! definition of materials container
    typedef std::map<std::string, IMaterial *> materials_t;

    //! return material from database
    const IMaterial *getMaterial(const std::string &name);

    //! add material to the database
    const IMaterial *addHomogeneousMaterial(const std::string &name, complex_t refractive_index);

    //! clean collection of material
    void clear();

    //! print material class
    friend std::ostream &operator<<(std::ostream &ostr, const MaterialManager &m) { m.print(ostr); return ostr; }

protected:
    MaterialManager(){}
    friend class ISingleton<MaterialManager >;

    //! print material class
    virtual void print(std::ostream &ostr) const;

    materials_t m_materials; //! container with defined materials
};

#endif // MATERIALMANAGER_H
