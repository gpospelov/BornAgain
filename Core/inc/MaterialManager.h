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
//! It is a singleton which provide common and unique interface for
//! material creation and access. No thread safeness.
//- -------------------------------------------------------------------
class MaterialManager: public ISingleton<MaterialManager>
{
public:
    //! return material from database
    const IMaterial *getMaterial(const std::string &name);

    //! add material to the database
    const IMaterial *addHomogeneousMaterial(const std::string &name, complex_t refractive_index);

    //! clean collection of material
    void clear();

    //! print material database
    void print() const;

private:
    typedef std::map<std::string, IMaterial *> materials_t;
    materials_t m_materials;
};

#endif // MATERIALMANAGER_H
