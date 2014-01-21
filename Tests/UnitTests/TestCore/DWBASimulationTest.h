#ifndef DWBASIMULATIONTEST_H
#define DWBASIMULATIONTEST_H


#include "DWBASimulation.h"
#include "MultiLayer.h"
#include "OutputDataFunctions.h"
#include "gtest/gtest.h"
#include "MaterialManager.h"
#include <boost/assign/list_of.hpp>


class DWBASimulationTest : public ::testing::Test
{
 protected:
    DWBASimulationTest();
    virtual ~DWBASimulationTest(){}

    Simulation m_sim;
    OutputData<double> m_data;
};


DWBASimulationTest::DWBASimulationTest()
{
    m_data.addAxis("x", 10, 0., 9.);
    m_data.addAxis("y", 5, 0., 4.);

    MultiLayer ml;
    m_sim.setDetectorParameters(m_data);
    m_sim.setSample(ml);
}


TEST_F(DWBASimulationTest, InitialState)
{
    DWBASimulation dwbasim;
    EXPECT_FALSE(dwbasim.hasPolarizedOutputData());
    EXPECT_EQ(1, dwbasim.getDWBAIntensity().getAllocatedSize());
}


TEST_F(DWBASimulationTest, InitialWithSimulation)
{

    DWBASimulation dwbasim;
    dwbasim.init(m_sim);
    EXPECT_EQ(m_data.getAllocatedSize(), dwbasim.getDWBAIntensity().getAllocatedSize());
    EXPECT_EQ(dwbasim.getDWBAIntensity().totalSum(), 0.0);
    m_data.setAllTo(1.0);
    dwbasim.addDWBAIntensity(m_data);
    EXPECT_EQ(dwbasim.getDWBAIntensity().totalSum(), 50.0);
}


TEST_F(DWBASimulationTest, ThreadIterator)
{
    DWBASimulation dwbasim;
    dwbasim.init(m_sim);

    int index(0);
    for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
        (*it) = double(index++);
    }

    ThreadInfo thread_info;
    thread_info.n_threads = 4;
    int istart[] = {0, 13, 26, 39};
    for(size_t i_thread=0; i_thread<4; i_thread++) {
        index = istart[i_thread];
        thread_info.current_thread = i_thread;
        dwbasim.setThreadInfo(thread_info);
        for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
            EXPECT_EQ((*it), (double)index++);
        }
    }

}

TEST_F(DWBASimulationTest, MaskedThreadIterator)
{
    int index(0);
    for(OutputData<double>::iterator it = m_data.begin(); it!=m_data.end(); ++it) {
        (*it) = double(index++);
    }

    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(m_data, 1.99, 0.99, 7.01, 3.01);
    m_data.setMask(*mask1);

    m_sim.setDetectorParameters(m_data);

    DWBASimulation dwbasim;
    dwbasim.init(m_sim);

    dwbasim.addDWBAIntensity(m_data);

    const int nthreads = 4;
    ThreadInfo thread_info;
    thread_info.n_threads = nthreads;

    std::vector<std::vector<int> > values;
    values.resize(nthreads);
    values[0] = boost::assign::list_of(11)(12);
    values[1] = boost::assign::list_of(13)(16)(17)(18)(21)(22)(23);
    values[2] = boost::assign::list_of(26)(27)(28)(31)(32)(33)(36)(37)(38);

    for(size_t i_thread=0; i_thread<4; i_thread++) {
        int index = 0;
        thread_info.current_thread = i_thread;
        dwbasim.setThreadInfo(thread_info);
        for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
            EXPECT_EQ((*it), values[i_thread][index++]);
        }
    }

}


TEST_F(DWBASimulationTest, PolarizedIntensity)
{
    MultiLayer ml;

    kvector_t magnetic_field(0.0, 0.0, 0.0);
    const IMaterial *magMaterial0 = MaterialManager::getHomogeneousMagneticMaterial("MagMat0", 6e-4, 2e-8, magnetic_field);
    Layer layer(magMaterial0, 20*Units::nanometer);
    ml.addLayer(layer);
    m_sim.setSample(ml);

    DWBASimulation dwbasim;
    dwbasim.init(m_sim);

    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity().getAllocatedSize(), m_data.getAllocatedSize());
    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity().getRank(), m_data.getRank());
    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity()[0](0,0), 0.0);
    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity()[0](0,1), 0.0);
    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity()[0](1,0), 0.0);
    EXPECT_EQ(dwbasim.getPolarizedDWBAIntensity()[0](1,1), 0.0);
}




#endif // DETECTORTEST_H
