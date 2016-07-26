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
#include "MinimizerFactory.h"
#include "MinimizerItemCatalogue.h"
#include "MinimizerOptions.h"
#include <QDebug>

// ----------------------------------------------------------------------------

const QString MinimizerItem::P_ALGORITHMS = "Algorithms";
const QString MinimizerItem::P_MAX_ITERATION_COUNT = "Max number of iterations";
const QString MinimizerItem::P_ERROR_DEFINITION = "Error definition";
const QString MinimizerItem::P_MAX_TOLERANCE = "Max tolerance";
const QString MinimizerItem::P_PRECISION = "Relative precision";

MinimizerItem::MinimizerItem(const QString &model_type)
    : SessionItem(model_type)
{
}

int MinimizerItem::maxIterationCount() const
{
    return getItemValue(P_MAX_ITERATION_COUNT).toInt();
}

// ----------------------------------------------------------------------------

const QString MinimizerContainerItem::P_MINIMIZERS = "Library";

MinimizerContainerItem::MinimizerContainerItem()
    : MinimizerItem(Constants::MinimizerContainerType)
{
    addGroupProperty(P_MINIMIZERS, Constants::MinimizerLibraryGroup)
            ->setToolTip(QStringLiteral("Minimizer library"));
    setGroupProperty(P_MINIMIZERS, Constants::MinuitMinimizerType);
}

std::unique_ptr<IMinimizer> MinimizerContainerItem::createMinimizer() const
{
    auto minimizer = static_cast<MinimizerItem*>(getGroupItem(P_MINIMIZERS));
    Q_ASSERT(minimizer);
    return minimizer->createMinimizer();
}

// ----------------------------------------------------------------------------

MinuitMinimizerItem::MinuitMinimizerItem()
    : MinimizerItem(Constants::MinuitMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::MinuitMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_ITERATION_COUNT, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

//    addProperty(MinimizerItem::P_ERROR_DEFINITION, 1.0)
//        ->setToolTip("Error definition (=1. for getting 1 sigma error for chi2 fits)");

//    addProperty(MinimizerItem::P_MAX_TOLERANCE, 0.01)
//        ->setToolTip("Tolerance on the function value at the minimum.");

//    addProperty(MinimizerItem::P_PRECISION, -1.0)
//        ->setToolTip("Relative floating point arithmetic precision (-1 - let Minimizer to decide.");

}

std::unique_ptr<IMinimizer> MinuitMinimizerItem::createMinimizer() const
{
    std::string minimizerName, minimizerAlgo;
    MinimizerItemCatalogue::domainMinimizerNames(this, minimizerName, minimizerAlgo);

    qDebug() << "MinuitMinimizerItem::createMinimizer()"
             << QString::fromStdString(minimizerName) << QString::fromStdString(minimizerAlgo);

    std::unique_ptr<IMinimizer> result(MinimizerFactory::createMinimizer(minimizerName, minimizerAlgo));
    result->getOptions()->setMaxIterations(maxIterationCount());

    return result;
}

// ----------------------------------------------------------------------------

// FIXME, TODO
// P_MAX_TOLERANCE should be disabled for all GSL algorithms, except LMAAlgorithmType

GSLMinimizerItem::GSLMinimizerItem()
    : MinimizerItem(Constants::GSLMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GSLMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_ITERATION_COUNT, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

//    addProperty(MinimizerItem::P_MAX_TOLERANCE, 0.01)
//        ->setToolTip("Tolerance on the function value at the minimum.");

}

std::unique_ptr<IMinimizer> GSLMinimizerItem::createMinimizer() const
{
    std::string minimizerName, minimizerAlgo;
    MinimizerItemCatalogue::domainMinimizerNames(this, minimizerName, minimizerAlgo);

    qDebug() << "MinuitMinimizerItem::createMinimizer()"
             << QString::fromStdString(minimizerName) << QString::fromStdString(minimizerAlgo);

    std::unique_ptr<IMinimizer> result(MinimizerFactory::createMinimizer(minimizerName, minimizerAlgo));
    result->getOptions()->setMaxIterations(maxIterationCount());

    return result;
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
    : MinimizerItem(Constants::GeneticMinimizerType)
{
    addProperty(MinimizerItem::P_ALGORITHMS,
        MinimizerItemCatalogue::getAlgorithmCombo(Constants::GeneticMinimizerType).getVariant());

    addProperty(MinimizerItem::P_MAX_ITERATION_COUNT, 0)
        ->setToolTip("Maximum number of allowed iterations (0 - let Minimizer to decide)");

}

std::unique_ptr<IMinimizer> GeneticMinimizerItem::createMinimizer() const
{
    std::string minimizerName, minimizerAlgo;
    MinimizerItemCatalogue::domainMinimizerNames(this, minimizerName, minimizerAlgo);

    qDebug() << "MinuitMinimizerItem::createMinimizer()"
             << QString::fromStdString(minimizerName) << QString::fromStdString(minimizerAlgo);

    std::unique_ptr<IMinimizer> result(MinimizerFactory::createMinimizer(minimizerName, minimizerAlgo));
    result->getOptions()->setMaxIterations(maxIterationCount());

    return result;
}

//GeneticMinimizerItem::~GeneticMinimizerItem()
//{

//}
