#include "SampleBuilderNode.h"
#include "MultiLayer.h"
#include "IMultiLayerBuilder.h"
#include "ParameterPool.h"
#include <memory>
#include <iostream>
#include <stdexcept>

class SampleBuilderNoteTest : public ::testing::Test
{
public:

    //! Returns test multilayer.
    static std::unique_ptr<MultiLayer> testMultiLayer(double length)
    {
        std::unique_ptr<MultiLayer> result(new MultiLayer);
        result->setCrossCorrLength(length); // used to check following cloning
        return result;
    }

    //! Test sample builder
    class TestBuilder : public IMultiLayerBuilder
    {
    public:
        explicit TestBuilder(double length=42.0) : m_length(length)
        {
            setName("TestBuilder");
            registerParameter("length", &m_length);
        }

        MultiLayer* buildSample() const { return testMultiLayer(m_length).release(); }
        double m_length;
    };

protected:
    SampleBuilderNoteTest() {}
};

//! Checks children and pool parameters.

TEST_F(SampleBuilderNoteTest, builderParameters)
{
    SampleBuilderNode builderNode;

    // initial state
    EXPECT_EQ(builderNode.parent(), nullptr);
    EXPECT_EQ(builderNode.getChildren().size(), 0u);
    EXPECT_EQ(builderNode.parameterPool()->size(), 0u);
    EXPECT_EQ(bool(builderNode), false);

    // setting builder
    std::shared_ptr<IMultiLayerBuilder> builder(new SampleBuilderNoteTest::TestBuilder(33.0));
    builderNode.setSampleBuilder(builder);
    EXPECT_EQ(bool(builderNode), true);

    // checks that still no children
    EXPECT_EQ(builderNode.parent(), nullptr);
    EXPECT_EQ(builderNode.getChildren().size(), 0u);

    // checks that  node has same parameters/name as sample builder
    EXPECT_EQ(builderNode.getName(), builder->getName());
    EXPECT_EQ(builder.use_count(), 2);
    ASSERT_EQ(builderNode.parameterPool()->parameterNames().size(), 1u);
    EXPECT_EQ(builderNode.parameterPool()->parameterNames()[0], "length");

    // checks sample creation
    EXPECT_EQ(builderNode.createMultiLayer()->crossCorrLength(), 33.0);

    // reset node to initial state
    builderNode.reset();
    EXPECT_EQ(builder.use_count(), 1);
    EXPECT_EQ(builderNode.parameterPool()->size(), 0u);
    EXPECT_THROW(builderNode.createMultiLayer(), std::runtime_error);
}

//! Checks assignment operator.

TEST_F(SampleBuilderNoteTest, assignmentOperator)
{
    SampleBuilderNode builderNode;
    std::shared_ptr<IMultiLayerBuilder> builder(new SampleBuilderNoteTest::TestBuilder(33.0));
    builderNode.setSampleBuilder(builder);

    // checking assignment
    SampleBuilderNode node2;
    node2 = builderNode;
    EXPECT_EQ(builder.use_count(), 3);
}
