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
    EXPECT_EQ(model.nRows(), 0u);
    EXPECT_EQ(model.nCols(), 0u);

    model.setData(test_data);
    EXPECT_EQ(model.data(), test_data);
    EXPECT_EQ(model.nRows(), 3u);
    EXPECT_EQ(model.nCols(), 2u);

    model.setData({});
    EXPECT_EQ(model.data(), csv::DataArray());
    EXPECT_EQ(model.nRows(), 0u);
    EXPECT_EQ(model.nCols(), 0u);
}

TEST_F(TestCsvImportData, test_data_columns)
{
    CsvImportData model;
    EXPECT_EQ(model.column(CsvImportData::Intensity), -1);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), -1);

    csv::DataArray test_data {{"1.0", "2.0"}, {"3.0", "4.0"}, {"5.0", "6.0"}};
    model.setData(test_data);

    int previous = model.setColumnAs(0, csv::_intensity_);
    EXPECT_EQ(previous, -1);
    EXPECT_EQ(model.column(CsvImportData::Intensity), 0);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), -1);

    previous = model.setColumnAs(1, csv::_intensity_);
    EXPECT_EQ(previous, 0);
    EXPECT_EQ(model.column(CsvImportData::Intensity), 1);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), -1);

    previous = model.setColumnAs(1, csv::_theta_);
    EXPECT_EQ(previous, -1);
    EXPECT_EQ(model.column(CsvImportData::Intensity), -1);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), 1);

    previous = model.setColumnAs(1, csv::_q_);
    EXPECT_EQ(previous, 1);
    EXPECT_EQ(model.column(CsvImportData::Intensity), -1);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), 1);

    previous = model.setColumnAs(0, csv::_intensity_);
    EXPECT_EQ(previous, -1);
    EXPECT_EQ(model.column(CsvImportData::Intensity), 0);
    EXPECT_EQ(model.column(CsvImportData::Coordinate), 1);

    EXPECT_EQ(model.valuesFromColumn(-1), csv::DataColumn());
    EXPECT_EQ(model.valuesFromColumn(2), csv::DataColumn());
    csv::DataColumn result0 {"1.0", "3.0", "5.0"};
    EXPECT_EQ(model.valuesFromColumn(0), result0);
    csv::DataColumn result1 {"2.0", "4.0", "6.0"};
    EXPECT_EQ(model.valuesFromColumn(1), result1);
}
