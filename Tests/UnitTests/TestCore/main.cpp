#include "gtest/gtest.h"

#include "AxisDoubleTest.h"
#include "BeamTest.h"
#include "ChiSquaredModuleTest.h"
#include "CVectorTest.h"
#include "DetectorTest.h"
#include "SimulationTest.h"
#include "InstrumentTest.h"
#include "IParameterizedTest.h"
#include "KVectorTest.h"
#include "MaskTest.h"
#include "OutputDataIteratorTest.h"
#include "OutputDataTest.h"
#include "ParameterPoolTest.h"
#include "RealParameterWrapperTest.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}

