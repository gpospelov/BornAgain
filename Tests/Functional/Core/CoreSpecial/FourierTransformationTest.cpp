// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/FourierTransformationTest.cpp
//! @brief     Implements FourierTransformationTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Instrument/OutputData.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <memory>
#include <vector>

namespace
{

const double threshold = 1e-10;

//! Returns file names to test fft.
std::vector<std::string> inputImages()
{
    return {"CylindersAndPrisms.int.gz", "RectDetectorGeneric.int.gz"};
}

//! Returns location of images to test fft.
std::string inputImageDir() { return BATesting::CoreReferenceDir(); }

//! Returns file names with paths to test fft.
std::vector<std::string> inputImageNames()
    {
    std::vector<std::string> result;
    for (auto name : inputImages())
        result.push_back(FileSystemUtils::jointPath(inputImageDir(), name));

    return result;
}

//! Returns name of directory with fft images for reference.
std::string fftReferenceDir() { return BATesting::CoreReferenceDir(); }

//! Returns name of fft image based on given image name.
std::string fftReferenceImage(const std::string& input_image)
    {
    auto filename = FileSystemUtils::filename(input_image);
    return FileSystemUtils::jointPath(fftReferenceDir(), "FourierTransformation_" + filename);
}

//! Returns name of directory for output fft images.
std::string outputDir() { return BATesting::CoreOutputDir(); }

//! Runs test over one image. Returns true upon success.
bool test_fft(const std::string& input_image_name, const std::string& reference_fft_name)
{
    std::cout << "\nFourierTransformationTest::test_fft()"
              << "\n";
    std::cout << "Input image: " << input_image_name << "\n";
    std::cout << "Reference fft: " << reference_fft_name << "\n";

    // loading input image
    std::unique_ptr<OutputData<double>> input_image;
    try {
        input_image.reset(IntensityDataIOFactory::readOutputData(input_image_name));
    } catch (const std::exception&) {
        std::cout << "Error: no input image.\n";
        return false;
    }

    // making fourier transformation
    std::unique_ptr<OutputData<double>> fft = IntensityDataFunctions::createFFT(*input_image.get());

    // loading reference fft
    std::unique_ptr<OutputData<double>> reference_fft;
    try {
        reference_fft.reset(IntensityDataIOFactory::readOutputData(reference_fft_name));
    } catch (const std::exception&) {
        std::cout << "Error: no reference fft image. Creating new one.\n";
    }

    // comparing new fft against reference fft, if exist
    bool success(false);
    if (reference_fft)
        success = IntensityDataFunctions::getRelativeDifference(*fft, *reference_fft) <= threshold;

    if (!success) {
        FileSystemUtils::createDirectory(outputDir());
        std::string out_fname =
            FileSystemUtils::jointPath(outputDir(), FileSystemUtils::filename(reference_fft_name));
        IntensityDataIOFactory::writeOutputData(*fft, out_fname);
        std::cout << "New fft image stored in " << out_fname << "\n";
    }

    return success;
}

} // namespace


class FourierTransformationTest : public ::testing::Test {};

TEST_F(FourierTransformationTest, FourierTransformation)
{
    for (auto inputImage : inputImageNames())
        EXPECT_TRUE(test_fft(inputImage, fftReferenceImage(inputImage)));
}
