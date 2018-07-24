// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/MinimizerTests.h
//! @brief     Defines classes MinimizerTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTESTS_H
#define MINIMIZERTESTS_H

#include "IObsoleteMinimizerTest.h"

//! basic test of Minuit2/Migrad minimizer
class Minuit2MigradTest : public IObsoleteMinimizerTest
{
public:
    Minuit2MigradTest();
};

//! basic test of Minuit2/Fumili minimizer
class Minuit2FumiliTest : public IObsoleteMinimizerTest
{
public:
    Minuit2FumiliTest();
};

//! basic test of GSL/LMA minimizer
class GSLLevenbergMarquardtTest : public IObsoleteMinimizerTest
{
public:
    GSLLevenbergMarquardtTest();
};

//! basic test of GSL/BFGS minimizer
class GSLMultiMinBFGSTest : public IObsoleteMinimizerTest
{
public:
    GSLMultiMinBFGSTest();
};

//! basic test of GSL/SteepestDescent minimizer
class GSLMultiMinSteepestDescentTest : public IObsoleteMinimizerTest
{
public:
    GSLMultiMinSteepestDescentTest();
};

//! basic test of GSL/SimulatedAnnealing minimizer
class GSLSimulatedAnnealingTest : public IObsoleteMinimizerTest
{
public:
    GSLSimulatedAnnealingTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

//! basic test of Genetic minimizer
class GeneticTest : public IObsoleteMinimizerTest
{
public:
    GeneticTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

#endif // MINIMIZERTESTS_H


