#include "google_test.h"
#include "CsvImportTable.h"


class TestCsvImportData : public ::testing::Test
{
public:
    ~TestCsvImportData() override;
};

TestCsvImportData::~TestCsvImportData() = default;

TEST_F(TestCsvImportData, test_setting_data)
{
    csv::DataArray test_data {{"1.0", "2.0"}, {"3.0", "4.0"}, {"5.0", "6.0"}};

    CsvImportData model;
    EXPECT_EQ(model.data(), csv::DataArray());
    model.setData(test_data);
    EXPECT_EQ(model.data(), test_data);
    model.setData({});
    EXPECT_EQ(model.data(), csv::DataArray());
}

TEST_F(TestCsvImportData, test_accessing_columns)
{
    CsvImportData model;
    EXPECT_EQ(model.column(CsvImportData::Intensity), -1);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), -1);
}
