#ifndef MINIMIZERFUNCTIONALTESTS_H
#define MINIMIZERFUNCTIONALTESTS_H

#include "IMinimizerFunctionalTest.h"

class Minuit2MigradTest : public IMinimizerFunctionalTest
{
public:
    Minuit2MigradTest();
};

class Minuit2FumiliTest : public IMinimizerFunctionalTest
{
public:
    Minuit2FumiliTest();
};

class GSLLevenbergMarquardtTest : public IMinimizerFunctionalTest
{
public:
    GSLLevenbergMarquardtTest();
};

class GSLMultiMinBFGSTest : public IMinimizerFunctionalTest
{
public:
    GSLMultiMinBFGSTest();
};

class GSLMultiMinSteepestDescentTest : public IMinimizerFunctionalTest
{
public:
    GSLMultiMinSteepestDescentTest();
};

class GSLSimulatedAnnealingTest : public IMinimizerFunctionalTest
{
public:
    GSLSimulatedAnnealingTest();
protected:
    FitSuite *createFitSuite();
};

class GeneticTest : public IMinimizerFunctionalTest
{
public:
    GeneticTest();
protected:
    FitSuite *createFitSuite();
};

#endif


