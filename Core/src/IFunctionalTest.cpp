#include "IFunctionalTest.h"
#include "Exceptions.h"

IFunctionalTest::IFunctionalTest()
{
}


void IFunctionalTest::execute()
{
    throw NotImplementedException("This test can't run.");
}

