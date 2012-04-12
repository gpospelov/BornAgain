#ifndef NAMEDVECTORTEST_H
#define NAMEDVECTORTEST_H

#include "NamedVector.h"

class NamedVectorTest : public ::testing::Test
{
protected:
    NamedVectorTest();

    NamedVector<float> floatAngleVector;
    NamedVector<double> doubleLengthVector;

};

NamedVectorTest::NamedVectorTest()
    : floatAngleVector("angle")
    , doubleLengthVector("length", 0.0, 0.1, 100)
{
}

#endif // NAMEDVECTORTEST_H
