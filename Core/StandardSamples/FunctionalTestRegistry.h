// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.h
//! @brief     Defines class FunctionalTestRegistry.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTREGISTRY_H
#define FUNCTIONALTESTREGISTRY_H


#include <string>
#include <map>
#include "IFunctionalTest.h"


//! @class FunctionalTestRegistry
//! @ingroup samples
//! @brief Enhances ParticleInfo by position in x and y.
//!
//! Note that position in z ("depth") is inherited from ParticleInfo.

class FunctionalTestRegistry
{
public:

    class Catalogue
    {
    public:
        typedef std::map<std::string, FunctionalTestInfo> catalogue_t;
        Catalogue();
        void add(const std::string &name, const std::string &description,
                 const std::string &reference, double threshold);
        void print();
        catalogue_t m_data;
        FunctionalTestInfo getInfo(const std::string &name);
    };

    void printCatalogue() { m_catalogue.print(); }

    FunctionalTest_t getTest(const std::string &name);

    //FunctionalTest_t runTest(const std::string &name);

    bool isRegisteredName(const std::string &name);

private:

    static Catalogue m_catalogue;
};


//! run functional tests with given name
int FUNCTIONAL_TEST(const std::string &name);



#endif
