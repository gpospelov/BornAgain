#include "google_test.h"
#include "tspectrum.h"
#include <iostream>

class SpectrumTest : public ::testing::Test
{
protected:
    ~SpectrumTest();

};

SpectrumTest::~SpectrumTest() = default;

TEST_F(SpectrumTest, initialState)
{
    std::vector<std::vector<double>> data = {
        {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0, 10.0, 1.0, 1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}
    };

    tspectrum::Spectrum2D finder;
    auto peaks = finder.find_peaks(data, 3, "nomarkov", 0.1);
    EXPECT_EQ(peaks.size(), 1u);
    EXPECT_NEAR(peaks[0].first, 3.0, 0.01); // rows
    EXPECT_NEAR(peaks[0].second, 4.0, 0.01); // cols
}
