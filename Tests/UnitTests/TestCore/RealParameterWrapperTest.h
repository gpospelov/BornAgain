#ifndef REALPARAMETERWRAPPERTEST_H
#define REALPARAMETERWRAPPERTEST_H

#include "IParameterized.h"
#include "RealParameterWrapper.h"
#include "Exceptions.h"

class RealParameterWrapperTest : public ::testing::Test
{
 protected:
    RealParameterWrapperTest() {}
    virtual ~RealParameterWrapperTest() {}

    class ParametrizedObject : public IParameterized
    {
    public:
        ParametrizedObject()
            : m_par1(17), m_changed(false)
        {
            registerParameter("ParametrizedObject", &m_par1);
        }
        virtual void onChange() final { m_changed = true; }
        double m_par1;
        bool m_changed;
    };
    ParametrizedObject obj1;

};

TEST_F(RealParameterWrapperTest, ParameterAccess)
{
    EXPECT_EQ( obj1.m_par1, 17. );
    RealParameterWrapper par11(&obj1, &(obj1.m_par1));
    EXPECT_EQ( obj1.m_par1, par11.getValue() );

    RealParameterWrapper par12 = par11;
    EXPECT_EQ( obj1.m_par1, par12.getValue() );

    obj1.m_par1 = 2;
    EXPECT_EQ( par11.getValue(), 2. );
    EXPECT_EQ( par12.getValue(), 2. );
    EXPECT_EQ( par11.getValue(), 2. );

    EXPECT_FALSE( obj1.m_changed );
    par11.setValue( 3.14 );
    EXPECT_EQ( par11.getValue(), 3.14 );
    EXPECT_EQ( par12.getValue(), par11.getValue() );
    EXPECT_TRUE( obj1.m_changed );

    std::vector<RealParameterWrapper > parameters;
    parameters.push_back(par11);
    parameters.push_back(par12);
    parameters[0].setValue(3.0);
    EXPECT_EQ( obj1.m_par1, 3. );
    EXPECT_EQ( parameters[1].getValue(), 3. );
}

TEST_F(RealParameterWrapperTest, LimitedParameter)
{
    /* TODO restore
    m_real_parameter = 1.0;
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::limited(10.0, 20.0)), OutOfBoundsException);
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::lowerLimited(2.0)), OutOfBoundsException);
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::upperLimited(0.0)), OutOfBoundsException);

    m_real_parameter = 15.0;
    AttLimits limits = AttLimits::limited(10, 20);
    RealParameterWrapper par1(&m_real_parameter, limits);

    par1.setValue(16.0);
    EXPECT_EQ(16.0, m_real_parameter);

    EXPECT_THROW(par1.setValue(21.0), OutOfBoundsException);
    EXPECT_EQ(16.0, m_real_parameter);

    RealParameterWrapper par2(par1);
    EXPECT_TRUE(par1.getAttLimits() == par2.getAttLimits());
    EXPECT_TRUE(par1 == par2);

    EXPECT_THROW(par1.setValue(21.0), OutOfBoundsException);
    EXPECT_EQ(16.0, m_real_parameter);

    par1.setValue(11.0);
    EXPECT_EQ(11.0, m_real_parameter);
    */
}

#endif // REALPARAMETERWRAPPERTEST_H
