#include "google_test.h"
#include "ComboProperty.h"
#include "test_utils.h"

class TestComboProperty :  public ::testing::Test
{
public:
    ~TestComboProperty();
    ComboProperty propertyFromXML(const QString& buffer) {
        return TestUtils::propertyFromXML<ComboProperty>(buffer);
    }

};

TestComboProperty::~TestComboProperty() = default;

TEST_F(TestComboProperty, test_ComboEquality)
{
    EXPECT_EQ(1, 1);
        ComboProperty c1;
        ComboProperty c2;
        EXPECT_TRUE(c1 == c2);

        c1 << "a1" << "a2";
        c2 << "a1" << "a2";
        EXPECT_TRUE(c1 == c2);

        c2 << "a3";
        EXPECT_TRUE(c1 != c2);
        c2.setValue("a2");
        EXPECT_TRUE(c1 != c2);

        c1 << "a3";
        c1.setValue("a2");
        EXPECT_TRUE(c1 == c2);
}

TEST_F(TestComboProperty, test_VariantEquality)
{
    QVariant v1(1.0);
    QVariant v2(2.0);
    QVariant v3(2.0);
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v2 == v3);

    ComboProperty c1 = ComboProperty() << "a1" << "a2";
    ComboProperty c2 = ComboProperty() << "a1" << "a2";
    EXPECT_TRUE(c1.variant() == c2.variant());

    c2 << "a3";
    EXPECT_TRUE(c1.variant() != c2.variant());
    c2.setValue("a2");
    EXPECT_TRUE(c1.variant() != c2.variant());

    c1 << "a3";
    c1.setValue("a2");
    EXPECT_TRUE(c1.variant() == c2.variant());
}

TEST_F(TestComboProperty, test_setValue)
{
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;

    EXPECT_EQ(combo.getValue(), QString("a1"));

    QStringList newValues = QStringList() << "b1" << "b2" << "b3";
    combo.setValues(newValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.getValues(), newValues);

    // checking that old value is preserved
    newValues = QStringList() << "c1" << "b1" << "c2";
    combo.setValues(newValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
    EXPECT_EQ(combo.getValues(), newValues);
}

TEST_F(TestComboProperty, test_currentIndex)
{
    ComboProperty combo;
    EXPECT_EQ(combo.currentIndex(), -1);
    combo << "c1" << "c2";
    EXPECT_EQ(combo.currentIndex(), 0);
    combo.setValue("c2");
    EXPECT_EQ(combo.currentIndex(), 1);

    combo.setCurrentIndex(0);
    EXPECT_EQ(combo.getValue(), QString("c1"));
}

TEST_F(TestComboProperty, test_stringOfValues)
{
    QStringList expectedValues = QStringList() << "a1" << "a2";
    ComboProperty combo = ComboProperty() << expectedValues;

    EXPECT_EQ(combo.stringOfValues(), QString("a1;a2"));

    // setting string of values, current value should change
    QString stringOfValues("b1;b2;b3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));

    // setting new string of values, containing current value. Current values should remain.
    stringOfValues = QString("c1;b1;c3");
    combo.setStringOfValues(stringOfValues);
    EXPECT_EQ(combo.stringOfValues(), stringOfValues);
    EXPECT_EQ(combo.getValue(), QString("b1"));
}

TEST_F(TestComboProperty, test_comboXML)
{
    // Writing combo to XML
    ComboProperty combo = ComboProperty() << "a1" << "a2" << "a3";

    QString expected = "<Parameter ParType=\"ComboProperty\" ParRole=\"0\" ParValue=\"0\" "
                       "ParExt=\"a1;a2;a3\"/>";
    EXPECT_EQ(TestUtils::propertyToXML(combo), expected);

    // reading from XML
    ComboProperty combo_property = propertyFromXML(expected);
    EXPECT_EQ(combo_property.getValue(), QString("a1"));
    EXPECT_EQ(combo_property.stringOfValues(), QString("a1;a2;a3"));
    EXPECT_TRUE(combo_property == combo);
}
