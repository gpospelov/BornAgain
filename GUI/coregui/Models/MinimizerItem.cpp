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

const QString MinimizerItem::P_MINIMIZER_LIBRARY = "Library";

MinimizerItem::MinimizerItem()
    : SessionItem(Constants::MinimizerType)
{
    addGroupProperty(P_MINIMIZER_LIBRARY, Constants::MinimizerLibraryGroup);
    addProperty("test", 99.0);

}

// ----------------------------------------------------------------------------

MinuitMinimizerItem::MinuitMinimizerItem()
    : SessionItem(Constants::MinuitMinimizerType)
{
    addProperty("A", 1.0);

}

// ----------------------------------------------------------------------------

GSLMinimizerItem::GSLMinimizerItem()
    : SessionItem(Constants::GSLMinimizerType)
{
    addProperty("B", 2.0);

}

GeneticMinimizerItem::GeneticMinimizerItem()
    : SessionItem(Constants::GeneticMinimizerType)
{
    addProperty("C", 3.0);

}
