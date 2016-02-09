// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/MinimizerFunctionalTests.h
//! @brief     Defines classes MinimizerFunctionalTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERFUNCTIONALTESTS_H
#define MINIMIZERFUNCTIONALTESTS_H

#include "IMinimizerFunctionalTest.h"

//! basic test of Minuit2/Migrad minimizer
class Minuit2MigradTest : public IMinimizerFunctionalTest
{
public:
    Minuit2MigradTest();
};

//! basic test of Minuit2/Fumili minimizer
class Minuit2FumiliTest : public IMinimizerFunctionalTest
{
public:
    Minuit2FumiliTest();
};

//! basic test of GSL/LMA minimizer
class GSLLevenbergMarquardtTest : public IMinimizerFunctionalTest
{
public:
    GSLLevenbergMarquardtTest();
};

//! basic test of GSL/BFGS minimizer
class GSLMultiMinBFGSTest : public IMinimizerFunctionalTest
{
public:
    GSLMultiMinBFGSTest();
};

//! basic test of GSL/SteepestDescent minimizer
class GSLMultiMinSteepestDescentTest : public IMinimizerFunctionalTest
{
public:
    GSLMultiMinSteepestDescentTest();
};

//! basic test of GSL/SimulatedAnnealing minimizer
class GSLSimulatedAnnealingTest : public IMinimizerFunctionalTest
{
public:
    GSLSimulatedAnnealingTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

//! basic test of Genetic minimizer
class GeneticTest : public IMinimizerFunctionalTest
{
public:
    GeneticTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

#endif


