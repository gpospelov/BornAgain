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
const QString MinimizerItem::P_MAX_NUMBER_OF_ITERATIONS = "Max number of iterations";
const QString MinimizerItem::P_ERROR_DEFINITION = "Error definition";
const QString MinimizerItem::P_MAX_TOLERANCE = "Max tolerance";
const QString MinimizerItem::P_PRECISION = "Relative precision";

MinimizerItem::MinimizerItem()
    : SessionItem(Constants::MinimizerType)
{
    addGroupProperty(P_MINIMIZER_LIBRARY, Constants::MinimizerLibraryGroup)
        ->setToolTip(QStringLiteral("Minimizer library"));
}

// ----------------------------------------------------------------------------

MinuitMinimizerItem::MinuitMinimizerItem()
    : SessionItem(Constants::MinuitMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::MinuitMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_NUMBER_OF_ITERATIONS, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

//    addProperty(MinimizerItem::P_ERROR_DEFINITION, 1.0)
//        ->setToolTip("Error definition (=1. for getting 1 sigma error for chi2 fits)");

//    addProperty(MinimizerItem::P_MAX_TOLERANCE, 0.01)
//        ->setToolTip("Tolerance on the function value at the minimum.");

//    addProperty(MinimizerItem::P_PRECISION, -1.0)
//        ->setToolTip("Relative floating point arithmetic precision (-1 - let Minimizer to decide.");

}

// ----------------------------------------------------------------------------

// FIXME, TODO
// P_MAX_TOLERANCE should be disabled for all GSL algorithms, except LMAAlgorithmType

GSLMinimizerItem::GSLMinimizerItem()
    : SessionItem(Constants::GSLMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GSLMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_NUMBER_OF_ITERATIONS, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

//    addProperty(MinimizerItem::P_MAX_TOLERANCE, 0.01)
//        ->setToolTip("Tolerance on the function value at the minimum.");

}

//pars.fPopSize = m_options.getIntValue("PopSize");
//pars.fNsteps = m_options.getMaxIterations();
//pars.fCycles = m_options.getIntValue("Cycles");
//pars.fSC_steps = m_options.getIntValue("SC_steps");
//pars.fSC_rate = m_options.getIntValue("SC_rate");
//pars.fSC_factor = m_options.getRealValue("SC_factor");
//pars.fConvCrit = 10.*m_options.getTolerance();
//pars.fSeed = m_options.getIntValue("RandomSeed");


GeneticMinimizerItem::GeneticMinimizerItem()
    : SessionItem(Constants::GeneticMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GeneticMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_NUMBER_OF_ITERATIONS, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

}
