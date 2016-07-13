// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/StandardFits/MinimizerTests.h
//! @brief     Declares classes MinimizerTests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERTESTS_H
#define MINIMIZERTESTS_H

#include "IMinimizerTest.h"

//! basic test of Minuit2/Migrad minimizer
class Minuit2MigradTest : public IMinimizerTest
{
public:
    Minuit2MigradTest();
};

//! basic test of Minuit2/Fumili minimizer
class Minuit2FumiliTest : public IMinimizerTest
{
public:
    Minuit2FumiliTest();
};

//! basic test of GSL/LMA minimizer
class GSLLevenbergMarquardtTest : public IMinimizerTest
{
public:
    GSLLevenbergMarquardtTest();
};

//! basic test of GSL/BFGS minimizer
class GSLMultiMinBFGSTest : public IMinimizerTest
{
public:
    GSLMultiMinBFGSTest();
};

//! basic test of GSL/SteepestDescent minimizer
class GSLMultiMinSteepestDescentTest : public IMinimizerTest
{
public:
    GSLMultiMinSteepestDescentTest();
};

//! basic test of GSL/SimulatedAnnealing minimizer
class GSLSimulatedAnnealingTest : public IMinimizerTest
{
public:
    GSLSimulatedAnnealingTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

//! basic test of Genetic minimizer
class GeneticTest : public IMinimizerTest
{
public:
    GeneticTest();
protected:
    std::unique_ptr<FitSuite> createFitSuite();
};

#endif // MINIMIZERTESTS_H


