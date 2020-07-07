// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItemCatalogue.cpp
//! @brief     Implements MinimizerItemCatalogue class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MinimizerItemCatalogue.h"
#include "Fit/Minimizer/MinimizerFactory.h"
#include "GUI/coregui/utils/GUIHelpers.h"

//! Returns ComboProperty representing list of algorithms defined for given minimizerType.

ComboProperty MinimizerItemCatalogue::algorithmCombo(const QString& minimizerType)
{
    ComboProperty result = ComboProperty() << algorithmNames(minimizerType);
    result.setToolTips(algorithmDescriptions(minimizerType));
    return result;
}

//! Returns list of algorithm names defined for given minimizer.

QStringList MinimizerItemCatalogue::algorithmNames(const QString& minimizerType)
{
    std::vector<std::string> algos =
        MinimizerFactory::catalogue().algorithmNames(minimizerType.toStdString());
    return GUIHelpers::fromStdStrings(algos);
}

//! Returns list of algoritm descriptions defined for given minimizer.

QStringList MinimizerItemCatalogue::algorithmDescriptions(const QString& minimizerType)
{
    std::vector<std::string> descr =
        MinimizerFactory::catalogue().algorithmDescriptions(minimizerType.toStdString());
    return GUIHelpers::fromStdStrings(descr);
}
