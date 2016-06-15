// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItemCatalogue.cpp
//! @brief     Implements MinimizerItemCatalogue class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MinimizerItemCatalogue.h"
#include "GUIHelpers.h"

MinimizerLibrary::Catalogue MinimizerItemCatalogue::m_catalogue = MinimizerLibrary::Catalogue();

//! Returns ComboProperty representing list of algorithms defined for given minimizerType.

ComboProperty MinimizerItemCatalogue::getAlgorithmCombo(const QString &minimizerType)
{
    ComboProperty result;

    std::list<std::string> algos = m_catalogue.algorithmTypes(minimizerType.toStdString());
    result << GUIHelpers::fromStdList(algos);

    std::list<std::string> descr = m_catalogue.algorithmDescriptions(minimizerType.toStdString());
    result.setToolTips(GUIHelpers::fromStdList(descr));

    return result;
}
