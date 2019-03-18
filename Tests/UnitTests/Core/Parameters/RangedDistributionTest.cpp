#include "google_test.h"
#include "Distributions.h"
#include "ParameterSample.h"
#include "RangedDistributions.h"

class RangedDistributionTest : public ::testing::Test
{
protected:
    ~RangedDistributionTest();

    void checkDefaults(const RangedDistribution& distr);

    template<class T>
    void checkThrows();

    template<class T>
    void checkStandardSampling();
};

RangedDistributionTest::~RangedDistributionTest() = default;

void RangedDistributionTest::checkDefaults(const RangedDistribution& distr)
{
    EXPECT_EQ(distr.nSamples(), 5u);
    EXPECT_EQ(distr.sigmaFactor(), 2.0);
    EXPECT_EQ(distr.limits(), RealLimits::limitless());
}

template<class T>
void RangedDistributionTest::checkThrows()
{
    EXPECT_THROW(T(0, 1.0, 0.0, 1.0), std::runtime_error);
    EXPECT_THROW(T(1, 0.0, 0.0, 1.0), std::runtime_error);
    EXPECT_THROW(T(1, 1.0, 1.0, -1.0), std::runtime_error);
    EXPECT_THROW(T(1, 1.0, 1.0, -1.0), std::runtime_error);
    EXPECT_THROW(T(8, 5.0, RealLimits::limited(1.0, 0.2)), std::runtime_error);
    EXPECT_THROW(T(8, -5.0), std::runtime_error);
    EXPECT_NO_THROW(T(1, 0.1, 0.0, 0.1));
    EXPECT_NO_THROW(T(1, 0.1));
    EXPECT_NO_THROW(T(2, 0.1));
}

template<class T>
void RangedDistributionTest::checkStandardSampling()
{
    T distr(3, 1.0);

    const double mean = 1.0;
    const double stddev = 0.5;

    EXPECT_THROW(distr.distribution(mean, -1.0), std::runtime_error);
    EXPECT_THROW(distr.generateSamples({mean, mean, mean}, {stddev, stddev}), std::runtime_error);
    EXPECT_NO_THROW(distr.distribution(mean, 0.0));

    auto distr_impl = distr.distribution(mean, stddev);
    EXPECT_DOUBLE_EQ(distr_impl->getMean(), mean);

    auto samples = distr.generateSamples(mean, stddev);
    double sum_weights = 0.0;
    for (size_t i = 0; i < samples.size(); ++i)
        sum_weights += samples[i].weight;
    EXPECT_DOUBLE_EQ(sum_weights, 1.0);
    EXPECT_EQ(samples.size(), 3u);

    auto samples_2 = distr.generateSamples({mean, mean, mean}, {stddev, stddev, stddev});
    for (size_t i = 0; i < samples_2.size(); ++i) {
        sum_weights = 0.0;
        for (size_t j = 0; j < samples_2[i].size(); ++j)
            sum_weights += samples_2[i][j].weight;
        EXPECT_DOUBLE_EQ(sum_weights, 1.0);
        EXPECT_EQ(samples_2[i].size(), 3u);
    }
    EXPECT_EQ(samples_2.size(), 3u);
}

TEST_F(RangedDistributionTest, DefaultConstructors)
{
    checkDefaults(RangedDistributionGate());
    checkDefaults(RangedDistributionLorentz());
    checkDefaults(RangedDistributionGaussian());
    checkDefaults(RangedDistributionLogNormal());
    checkDefaults(RangedDistributionCosine());
}

TEST_F(RangedDistributionTest, GateDistribution)
{
    checkThrows<RangedDistributionGate>();
    checkStandardSampling<RangedDistributionGate>();
}

TEST_F(RangedDistributionTest, LorentzDistribution)
{
    checkThrows<RangedDistributionLorentz>();
    checkStandardSampling<RangedDistributionLorentz>();
}

TEST_F(RangedDistributionTest, GaussianDistribution)
{
    checkThrows<RangedDistributionGaussian>();
    checkStandardSampling<RangedDistributionGaussian>();
}

TEST_F(RangedDistributionTest, LogNormalDistribution)
{
    checkThrows<RangedDistributionLogNormal>();
    checkStandardSampling<RangedDistributionLogNormal>();

    RangedDistributionLogNormal log_norm;
    EXPECT_THROW(log_norm.distribution(-1.0, 1.0), std::runtime_error);
}

TEST_F(RangedDistributionTest, CosineDistribution)
{
    checkThrows<RangedDistributionCosine>();
    checkStandardSampling<RangedDistributionCosine>();
}
