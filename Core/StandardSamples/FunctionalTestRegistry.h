// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestRegistry.h
//! @brief     Defines class FunctionalTestRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTREGISTRY_H
#define FUNCTIONALTESTREGISTRY_H


#include <string>
#include <map>
#include "IFunctionalTest.h"


//! @class FunctionalTestRegistry
//! @ingroup standard_samples
//! @brief The registry which holds information about available functional tests.

class BA_CORE_API_ FunctionalTestRegistry
{
public:

    class Catalogue
    {
    public:
        typedef std::map<std::string, FunctionalTestInfo> catalogue_t;
        Catalogue();
        void add(const std::string &name, const std::string &description,
                 const std::string &reference, double threshold, bool normalize = false);
        void print();
        catalogue_t m_data;
        FunctionalTestInfo getInfo(const std::string &name);
    };

    void printCatalogue() { m_catalogue.print(); }

    FunctionalTest* getTest(const std::string &name);

    bool isRegisteredName(const std::string &name);

private:

    static Catalogue m_catalogue;
};


//! run functional tests with given name
BA_CORE_API_ int FUNCTIONAL_TEST(const std::string &name);



#endif
