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
#include "AlgorithmNames.h"
#include "GUIHelpers.h"
#include "MinimizerItem.h"

MinimizerLibrary::Catalogue MinimizerItemCatalogue::m_catalogue = MinimizerLibrary::Catalogue();

//! Returns ComboProperty representing list of algorithms defined for given minimizerType.

ComboProperty MinimizerItemCatalogue::getAlgorithmCombo(const QString& minimizerType)
{
    ComboProperty result;

    std::list<std::string> algos = m_catalogue.algorithmTypes(minimizerType.toStdString());
    result << GUIHelpers::fromStdList(algos);

    std::list<std::string> descr = m_catalogue.algorithmDescriptions(minimizerType.toStdString());
    result.setToolTips(GUIHelpers::fromStdList(descr));

    return result;
}


//! !!! FIXME TODO WILL BE REFACTORED IN NEXT SPRINT (Sprint32)
//! Class provides temporary(!) FIXME translation of GUI minimizer names to domain names.
//! FIXME Will be refactored together with MinimizerFactory and MinimizerLibrary (in Sprint32).
//! !!!

void MinimizerItemCatalogue::domainMinimizerNames(
    const MinimizerItem* minimizer, std::string& domainName, std::string& domainAlgo)
{
    domainName.clear();;
    domainAlgo.clear();

    QString minimizerType = minimizer->modelType();

    ComboProperty combo = minimizer->getItemValue(MinimizerItem::P_ALGORITHMS)
        .value<ComboProperty>();
    QString algorithmName = combo.getValue();

    if(minimizerType == Constants::MinuitMinimizerType) {
        domainName = std::string("Minuit2");
        domainAlgo = algorithmName.toStdString();
    }

    else if(minimizerType == Constants::GSLMinimizerType) {
        if(algorithmName.toStdString() != AlgorithmNames::LMA) {
            domainName = std::string("GSLMultiMin");
            domainAlgo = algorithmName.toStdString();
        } else {
            domainName = std::string("GSLLMA");
            domainAlgo = std::string("");
        }
    } else if(minimizerType == Constants::GeneticMinimizerType) {
        domainName = std::string("Genetic");
        domainAlgo = std::string("");
    }
}
