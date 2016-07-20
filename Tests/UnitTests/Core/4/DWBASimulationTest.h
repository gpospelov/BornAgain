#ifndef DWBASIMULATIONTEST_H
#define DWBASIMULATIONTEST_H

#include "DWBASimulation.h"
#include "MultiLayer.h"
#include "OutputDataFunctions.h"
#include "SimulationElement.h"

class DWBASimulationTest : public ::testing::Test
{
 protected:
    DWBASimulationTest();
    virtual ~DWBASimulationTest(){}

    GISASSimulation m_sim;
    OutputData<double> m_data;
    std::vector<SimulationElement> m_sim_elements;
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
    EXPECT_EQ( size_t(1), dwbasim.getDWBAIntensity().getAllocatedSize());
}


//TEST_F(DWBASimulationTest, InitialWithSimulation)
//{

//    DWBASimulation dwbasim;
//    dwbasim.init(m_sim, m_sim_elements.begin(), m_sim_elements.end());
//    EXPECT_EQ(m_data.getAllocatedSize(), dwbasim.getDWBAIntensity().getAllocatedSize());
//    EXPECT_EQ(dwbasim.getDWBAIntensity().totalSum(), 0.0);
//    m_data.setAllTo(1.0);
//    dwbasim.addDWBAIntensity(m_data);
//    EXPECT_EQ(dwbasim.getDWBAIntensity().totalSum(), 50.0);
//}


//TEST_F(DWBASimulationTest, ThreadIterator)
//{
//    DWBASimulation dwbasim;
//    dwbasim.init(m_sim, m_sim_elements.begin(), m_sim_elements.end());

//    int index(0);
//    for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
//        (*it) = double(index++);
//    }

//    ThreadInfo thread_info;
//    thread_info.n_threads = 4;
//    int istart[] = {0, 13, 26, 39};
//    for(size_t i_thread=0; i_thread<4; i_thread++) {
//        index = istart[i_thread];
//        thread_info.current_thread = i_thread;
//        dwbasim.setThreadInfo(thread_info);
//        for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
//            EXPECT_EQ((*it), (double)index++);
//        }
//    }

//}

//TEST_F(DWBASimulationTest, MaskedThreadIterator)
//{
//    int index(0);
//    for(OutputData<double>::iterator it = m_data.begin(); it!=m_data.end(); ++it) {
//        (*it) = double(index++);
//    }

//    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(m_data, 1.99, 0.99, 7.01, 3.01, true);
//    m_data.setMask(*mask1);

//    m_sim.setDetectorParameters(m_data);

//    DWBASimulation dwbasim;
//    dwbasim.init(m_sim, m_sim_elements.begin(), m_sim_elements.end());

//    dwbasim.addDWBAIntensity(m_data);

//    const int nthreads = 4;
//    ThreadInfo thread_info;
//    thread_info.n_threads = nthreads;

//    std::vector<std::vector<int> > values;
//    values.resize(nthreads);
//    values[0] = boost::assign::list_of(11)(12);
//    values[1] = boost::assign::list_of(13)(16)(17)(18)(21)(22)(23);
//    values[2] = boost::assign::list_of(26)(27)(28)(31)(32)(33)(36)(37)(38);

//    for(size_t i_thread=0; i_thread<4; i_thread++) {
//        int index = 0;
//        thread_info.current_thread = i_thread;
//        dwbasim.setThreadInfo(thread_info);
//        for(DWBASimulation::iterator it = dwbasim.begin(); it!=dwbasim.end(); ++it) {
//            EXPECT_EQ((*it), values[i_thread][index++]);
//        }
//    }

//}

#endif // DWBASIMULATIONTEST_H
