// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.cpp
//! @brief     Implements class FunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObsoleteFunctionalTestRegistry.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

#include <boost/scoped_ptr.hpp>

ObsoleteFunctionalTestRegistry::Catalogue ObsoleteFunctionalTestRegistry::m_catalogue = ObsoleteFunctionalTestRegistry::Catalogue();


ObsoleteFunctionalTestRegistry::Catalogue::Catalogue()
{
    add("isgisaxs01",
        "Mixture of cylinders and prisms without interference",
        "isgisaxs01_reference.int.gz", 2e-10);

    add("isgisaxs04_1DDL",
        "Radial paracrystal",
        "isgisaxs04_reference_1DDL.int.gz", 2e-10);

    add("isgisaxs04_2DDL",
        "2D paracrystal",
        "isgisaxs04_reference_2DDLh.int.gz", 2e-10);




    add("isgisaxs02",
        "Mixture cylinder particles with different size distribution",
        "isgisaxs02_reference.int.gz", 2e-10);

    add("cylinders_ba",
        "Cylinder formfactor in BA",
        "isgisaxs03_reference_BA.int.gz", 2e-10);
    add("cylinders_dwba",
        "Cylinder formfactor in DWBA",
        "isgisaxs03_reference_DWBA.int.gz", 2e-10);
    add("cylinders_basize",
        "Cylinder formfactor in BA with size distribution",
        "isgisaxs03_reference_BA_size.int.gz", 2e-10);

    add("isgisaxs06a",
        "2D lattice with disorders",
        "isgisaxs06_reference_lattice.int.gz", 2e-10);
    add("isgisaxs06b",
        "2D lattice centered",
        "isgisaxs06_reference_centered.int.gz", 2e-10);
    add("isgisaxs06c",
        "2D lattice rotated",
        "isgisaxs06_reference_rotated.int.gz", 2e-10);
// this test is complicated for given Registry, see Tests/FunctionalTest/TesCore/IsGISAXS06L4
//    add("isgisaxs06_lattice4",
//        "2D lattice variants",
//        "isgisaxs06_reference_variants.int.gz", 2e-10);

    add("isgisaxs07",
        "Mixture of different particles a la IsGISAXS morphology file",
        "isgisaxs07_reference.int.gz", 2e-10);

    add("isgisaxs08a",
        "2DDL paracrystal lattice",
        "isgisaxs08_reference_2DDL_lattice.int.gz", 3e-10);
    add("isgisaxs08b",
        "2D paracrystal lattice with isotropic pdfs",
        "isgisaxs08_reference_2DDL_lattice2.int.gz", 2e-10);

    add("isgisaxs09a",
        "Pyramids on top of substrate",
        "isgisaxs09_reference_pyramid_Z0.int.gz", 2e-10);
    add("isgisaxs09b",
        "Rotated pyramids on top of substrate",
        "isgisaxs09_reference_pyramid_Z45.int.gz", 2e-10);

    add("isgisaxs10",
        "Cylinders with interference on top of substrate",
        "isgisaxs10_reference.int.gz", 2e-10);

    add("isgisaxs11",
        "Core shell nanoparticles",
        "isgisaxs11_reference.int.gz", 2e-10);

    add("isgisaxs15",
        "Size spacing correlation approximation",
        "isgisaxs15_reference.int.gz", 2e-10);

    add("mesocrystal01",
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles",
        "mesocrystal01_reference.int.gz", 1e-10, true);

    add("polmagcylinders1",
        "Polarized DWBA with zero magnetic field",
        "polmagcylinders1_reference.int.gz", 1e-10);
    // this test is complicated for given Registry
  //  add("polmagcylinders2",
  //      "Polarized DWBA with zero magnetic field",
  //      "isgi_cylinder_DWBA.ima.gz", 1e-10);

    add("LayerWithRoughness",
        "Layers with correlated roughness",
        "roughness01_reference.int.gz", 1e-10);

    add("ripple2",
        "Triangular ripple within the 1D-paracrystal model",
        "ripple2_sym_reference.int.gz", 1e-10);

    add("ripple1",
        "Cosine ripple within the 1D-paracrystal model",
        "ripple1_reference.int.gz", 1e-10);

}


void ObsoleteFunctionalTestRegistry::Catalogue::add(const std::string &name,
    const std::string &description, const std::string &reference, double threshold, bool normalize)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it != m_data.end() ) {
        throw ExistingClassRegistrationException("FunctionalTestRegistry::Catalogue::add() -> "
                                                 "Error. Existing item " +name);
    }
    m_data[name] = ObsoleteFunctionalTestInfo(name, description, reference, threshold, normalize);
}


void ObsoleteFunctionalTestRegistry::Catalogue::print()
{
    std::cout << "--- FunctionalTestRegistry::Catalogue::print() ---" << std::endl;
    for(catalogue_t::iterator it = m_data.begin(); it!= m_data.end(); ++it) {
        ObsoleteFunctionalTestInfo &info = (*it).second;
        std::cout << Utils::AdjustStringLength(info.m_name, 20) << " | "
                  << Utils::AdjustStringLength(info.m_description, 40) << " | "
                  << Utils::AdjustStringLength(info.m_reference_file, 40) << " | "
                  << std::setw(6) << std::left  << info.m_threshold << std::endl;
    }
}


ObsoleteFunctionalTestInfo ObsoleteFunctionalTestRegistry::Catalogue::getInfo(const std::string &name)
{
    catalogue_t::iterator it = m_data.find(name);
    if( it == m_data.end() ) {
        std::ostringstream ostr;
        ostr << "FunctionalTestRegistry::Catalogue::getInfo() -> Error. "
             << "Not existing test name '" << name << "'. "
             << "Existing items are:" << std::endl;
        for(catalogue_t::iterator it2 = m_data.begin(); it2!=m_data.end(); ++it2) {
            ostr << (*it2).first << std::endl;
        }
        throw ExistingClassRegistrationException(ostr.str());
    }
    return m_data[name];
}


bool ObsoleteFunctionalTestRegistry::isRegisteredName(const std::string &name)
{
    if( m_catalogue.m_data.find(name) == m_catalogue.m_data.end() ) {
        return false;
    } else {
        return true;
    }
}


ObsoleteFunctionalTest* ObsoleteFunctionalTestRegistry::getTest(const std::string &name)
{
    ObsoleteFunctionalTest* test = new ObsoleteFunctionalTest(m_catalogue.getInfo(name));
    return test;
}


int FUNCTIONAL_TEST(const std::string &name)
{
    ObsoleteFunctionalTestRegistry registry;
    boost::scoped_ptr<ObsoleteFunctionalTest> P_test(registry.getTest(name));
    P_test->runTest();
    return P_test->analyseResults();
}


