#include "google_test.h"
#include "BornAgainNamespace.h"
#include "ChiSquaredModule.h"
#include "VarianceFunctions.h"
#include "OutputData.h"

// TODO revise test

class ChiSquaredModuleTest : public ::testing::Test
{
protected:
    ~ChiSquaredModuleTest();

    ChiSquaredModule m_chi_empty;
    ChiSquaredModule m_chi_default;
    OutputData<double> m_real_data;
    OutputData<double> m_simul_data;
};

ChiSquaredModuleTest::~ChiSquaredModuleTest() = default;

TEST_F(ChiSquaredModuleTest, InitialState)
{
    EXPECT_TRUE(dynamic_cast<const VarianceDefaultFunction*>(m_chi_empty.varianceFunction()));
    EXPECT_EQ(nullptr, m_chi_empty.getIntensityFunction());
}

TEST_F(ChiSquaredModuleTest, CloneOfEmpty)
{
    ChiSquaredModule* clone_of_empty = m_chi_empty.clone();
    EXPECT_TRUE(dynamic_cast<const VarianceDefaultFunction*>(clone_of_empty->varianceFunction()));
    EXPECT_EQ(nullptr, clone_of_empty->getIntensityFunction());
    delete clone_of_empty;
}
