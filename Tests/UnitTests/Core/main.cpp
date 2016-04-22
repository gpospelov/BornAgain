#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif
#include "gtest/gtest.h"

#include "AttLimitsTest.h"
#include "BeamTest.h"
#include "ChiSquaredModuleTest.h"
#include "CVectorTest.h"
#include "DetectorTest.h"
#include "DistributionsTest.h"
#include "DistributionHandlerTest.h"
#include "DWBASimulationTest.h"
#include "FormFactorTest.h"
#include "InstrumentTest.h"
#include "IParameterizedTest.h"
#include "KVectorTest.h"
#include "LayerTest.h"
#include "MaskTest.h"
#include "OutputDataIteratorTest.h"
#include "OutputDataTest.h"
#include "ParameterDistributionTest.h"
#include "ParameterPoolTest.h"
#include "ParticleTest.h"
#include "RealParameterWrapperTest.h"
#include "GISASSimulationTest.h"
#include "ThreadInfoTest.h"
#include "ParticleCompositionTest.h"
#include "LayerRoughnessTest.h"
#include "LLDataTest.h"
#include "TRangeTest.h"
#include "FTDistributionsTest.h"
#include "MultiLayerTest.h"
#include "ParticleLayoutTest.h"
#include "HomogeneousMaterialTest.h"
#include "HomogeneousMagneticMaterialTest.h"
#include "ScalarRTCoefficientsTest.h"
#include "SpecularMatrixTest.h"
#include "MatrixRTCoefficientsTest.h"
#include "ScalarSpecularInfoMapTest.h"
#include "MatrixSpecularInfoMapTest.h"
#include "FixedBinAxisTest.h"
#include "VariableBinAxisTest.h"
#include "ConstKBinAxisTest.h"
#include "CustomBinAxisTest.h"
#include "IntensityDataFunctionsTest.h"
#include "SpecularSimulationTest.h"
#include "ParticleCoreShellTest.h"
#include "ParameterDistributionTest.h"
#include "UtilsTest.h"
#include "CumulativeValueTest.h"
#include "Histogram1DTest.h"
#include "Histogram2DTest.h"
#include "PolygonTest.h"
#include "DetectorMaskTest.h"
#include "Shape2DTest.h"
#include "RectangularDetectorTest.h"
#include "SpecialFunctionsTest.h"
#include "PrecomputedTest.h"


struct ErrorStreamRedirect {
    ErrorStreamRedirect( std::streambuf * new_buffer )
        : old( std::cerr.rdbuf( new_buffer ) )
    { }

    ~ErrorStreamRedirect( ) {
        std::cerr.rdbuf( old );
    }

private:
    std::streambuf * old;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}
