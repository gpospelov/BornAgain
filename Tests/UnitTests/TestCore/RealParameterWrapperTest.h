#ifndef REALPARAMETERWRAPPERTEST_H
#define REALPARAMETERWRAPPERTEST_H

#include "RealParameterWrapper.h"
#include "Exceptions.h"

class RealParameterWrapperTest : public ::testing::Test
{
 protected:
    RealParameterWrapperTest();
    virtual ~RealParameterWrapperTest();

    double m_real_parameter;
    RealParameterWrapper m_null_par;

    class ObjectToNotify
    {
    public:
        void set_status_true() { m_status = true; }
        void set_status_false() { m_status = false; }
        bool m_status;
    };
};


RealParameterWrapperTest::RealParameterWrapperTest() : m_real_parameter(3.141), m_null_par(0)
{

}

RealParameterWrapperTest::~RealParameterWrapperTest()
{

}

TEST_F(RealParameterWrapperTest, InitialState)
{
    EXPECT_TRUE( m_null_par.isNull() );
    ASSERT_THROW( m_null_par.getValue(), NullPointerException );
    ASSERT_THROW( m_null_par.setValue(1.0), NullPointerException );

    RealParameterWrapper par(m_null_par);
    EXPECT_TRUE( par.isNull() );
    ASSERT_THROW( par.getValue(), NullPointerException );
    ASSERT_THROW( par.setValue(1.0), NullPointerException );

    EXPECT_EQ(par.getAttLimits(), AttLimits::limitless());
}

TEST_F(RealParameterWrapperTest, ParameterAccess)
{
    RealParameterWrapper par11(&m_real_parameter);
    EXPECT_EQ( m_real_parameter, par11.getValue() );

    RealParameterWrapper par12 = par11;
    EXPECT_EQ( m_real_parameter, par12.getValue() );

    m_real_parameter = 2.0;
    EXPECT_EQ(  double(2.0), par11.getValue() );
    EXPECT_EQ(  double(2.0), par12.getValue() );
    std::vector<RealParameterWrapper > parameters;
    parameters.push_back(par11);
    parameters.push_back(par12);

    parameters[0].setValue(3.0);
    EXPECT_EQ(  double(3.0), m_real_parameter );
    EXPECT_EQ(  double(3.0), parameters[1].getValue() );
}

//TEST_F(RealParameterWrapperTest, ParameterSignals)
//{
//    // check that parameter emmits signals to two objects
//    m_real_parameter = 1.0;
//    RealParameterWrapper par(&m_real_parameter);
//    ObjectToNotify obj1, obj2;
//    RealParameterWrapper::signal_t::slot_type fun1 = boost::bind(&ObjectToNotify::set_status_true, &obj1);
//    RealParameterWrapper::signal_t::slot_type fun2 = boost::bind(&ObjectToNotify::set_status_true, &obj2);
//    par.connect(fun1);
//    par.connect(fun2);
//    obj1.m_status = false;
//    obj2.m_status = false;
//    par.setValue(2.0); // at this point status of object has to be changed by signal emmited from the parameter
//    EXPECT_TRUE( obj1.m_status );
//    EXPECT_TRUE( obj2.m_status );
//    // par2 should not emmit signals since they are not copied
//    RealParameterWrapper par2 = par;
//    obj1.m_status = false;
//    obj2.m_status = false;
//    par2.setValue(3.0);
//    EXPECT_FALSE( obj1.m_status );
//    EXPECT_FALSE( obj2.m_status );
//}

TEST_F(RealParameterWrapperTest, LimitedParameter)
{
    m_real_parameter = 1.0;
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::limited(10.0, 20.0)), OutOfBoundsException);
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::lowerLimited(2.0)), OutOfBoundsException);
    EXPECT_THROW(RealParameterWrapper(&m_real_parameter, AttLimits::upperLimited(0.0)), OutOfBoundsException);

    m_real_parameter = 15.0;
    AttLimits limits = AttLimits::limited(10, 20);
    RealParameterWrapper par1(&m_real_parameter, limits);

    EXPECT_TRUE(par1.setValue(16.0));
    EXPECT_EQ(16.0, m_real_parameter);

    EXPECT_FALSE(par1.setValue(21.0));
    EXPECT_EQ(16.0, m_real_parameter);

    RealParameterWrapper par2(par1);
    EXPECT_TRUE(par1.getAttLimits() == par2.getAttLimits());
    EXPECT_TRUE(par1 == par2);

    EXPECT_FALSE(par1.setValue(21.0));
    EXPECT_EQ(16.0, m_real_parameter);

    EXPECT_TRUE(par1.setValue(11.0));
    EXPECT_EQ(11.0, m_real_parameter);
}

#endif // REALPARAMETERWRAPPERTEST_H
