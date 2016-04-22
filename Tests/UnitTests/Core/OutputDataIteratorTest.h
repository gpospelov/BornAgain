#ifndef OUTPUTDATAITERATORTEST_H_
#define OUTPUTDATAITERATORTEST_H_

#include "OutputDataIterator.h"

#include "gtest/gtest.h"

class OutputDataIteratorTest : public ::testing::Test
{
 protected:
    OutputDataIteratorTest();
    virtual ~OutputDataIteratorTest();

    OutputData<double> *p_data;
    Mask *p_default_mask;
    Mask *p_modulo_mask;
};

OutputDataIteratorTest::OutputDataIteratorTest()
{
    p_data = new OutputData<double>();
    int *dims = new int[2];
    dims[0] = 3;
    dims[1] = 5;
    p_data->setAxisSizes(2, dims);
    double value = 0.0;
    OutputData<double>::iterator it = p_data->begin();
    while (it != p_data->end()) {
        *it = value;
        value += 1.0;
        ++it;
    }

    p_default_mask = new Mask();

    p_modulo_mask = new MaskIndexModulus(3, 1);

}

OutputDataIteratorTest::~OutputDataIteratorTest()
{
    delete p_data;
}

TEST_F(OutputDataIteratorTest, IterateWithoutMask)
{
    OutputData<double>::iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, p_data->end());
    ++it;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, ConstIterateWithoutMask)
{
    OutputData<double>::const_iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, p_data->end());
    ++it;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, IterateDefaultMask)
{
    p_data->addMask(*p_default_mask);
    OutputData<double>::iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    it++;
    EXPECT_EQ(it, p_data->end());
    it++;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, ConstIterateDefaultMask)
{
    p_data->addMask(*p_default_mask);
    OutputData<double>::const_iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    it++;
    EXPECT_EQ(it, p_data->end());
    it++;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, IterateCompoundMask)
{
    p_data->addMask(*p_default_mask);
    OutputData<double>::iterator it = p_data->begin();
    it.addMask(*p_modulo_mask);
    EXPECT_EQ(1.0, *it);
    for (size_t i=0; i<4; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(13.0, *it);
    it++;
    EXPECT_EQ(it, p_data->end());
    it++;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, ConstIterateCompoundMask)
{
    p_data->addMask(*p_default_mask);
    OutputData<double>::const_iterator it = p_data->begin();
    it.addMask(*p_modulo_mask);
    EXPECT_EQ(1.0, *it);
    double value;
    for (size_t i=0; i<4; ++i) {
        value = *it++;
    }
    EXPECT_DOUBLE_EQ(10.0, value);
    EXPECT_DOUBLE_EQ(13.0, *it);
    ++it;
    EXPECT_EQ(it, p_data->end());
    ++it;
    EXPECT_EQ(it, p_data->end());
}

#endif /* OUTPUTDATAITERATORTEST_H_ */
