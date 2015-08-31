#include "StandardFitsFactory.h"
#include "MinimizerFunctionalTests.h"

StandardFitsFactory::StandardFitsFactory()
{
    registerItem(
        "Minuit2Migrad",
        IFactoryCreateFunction<Minuit2MigradTest, IFunctionalTest>,
        "Functional test of Minuit2 minimizer with Migrad algorithm");

}
