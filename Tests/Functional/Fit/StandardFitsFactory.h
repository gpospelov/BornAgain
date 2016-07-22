// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/StandardFits/StandardFitsFactory.h
//! @brief     Declares class StandardFitsFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDFITSFACTORY_H
#define STANDARDFITSFACTORY_H

#include "IFactory.h" // inheriting from

class IFunctionalTest;

//! @class StandardFitsFactory
//! @ingroup standard_samples
//! @brief Factory to create predefined functional fit tests

class StandardFitsFactory : public IFactory<std::string, IFunctionalTest>
{
public:
    StandardFitsFactory();

    IFunctionalTest *createTest(const std::string &test_name);

    bool isValidTest(const std::string &test_name);

    void printCatalogue(std::ostream &ostr);
};

#endif // STANDARDFITSFACTORY_H
