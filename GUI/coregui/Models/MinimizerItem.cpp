// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItem.cpp
//! @brief     Implements MinimizerItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MinimizerItem.h"
#include "MinimizerItemCatalogue.h"
#include "ComboProperty.h"

const QString MinimizerItem::P_MINIMIZER_LIBRARY = "Library";
const QString MinimizerItem::P_ALGORITHMS = "Algorithms";

MinimizerItem::MinimizerItem()
    : SessionItem(Constants::MinimizerType)
{
    addGroupProperty(P_MINIMIZER_LIBRARY, Constants::MinimizerLibraryGroup)
        ->setToolTip(QStringLiteral("Minimizer library"));
    addProperty("test", 99.0);

}

// ----------------------------------------------------------------------------

MinuitMinimizerItem::MinuitMinimizerItem()
    : SessionItem(Constants::MinuitMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::MinuitMinimizerType).getVariant());
}

// ----------------------------------------------------------------------------

GSLMinimizerItem::GSLMinimizerItem()
    : SessionItem(Constants::GSLMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GSLMinimizerType).getVariant());

}

GeneticMinimizerItem::GeneticMinimizerItem()
    : SessionItem(Constants::GeneticMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GeneticMinimizerType).getVariant());

}
