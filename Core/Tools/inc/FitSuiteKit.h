#ifndef FITSUITEKIT_H
#define FITSUITEKIT_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteKit.h
//! @brief  Definition of FitSuiteKit class
//! @author Scientific Computing Group at FRM II
//! @date   15.11.2012


#include "Experiment.h"
#include "OutputData.h"

#include <vector>


//- -------------------------------------------------------------------
//! @class FitSuiteKit
//! @brief Class containing vector of pairs  (experiment, real data) for fit.
//! It doesn't own what it holds
//- -------------------------------------------------------------------
class FitSuiteKit
{
public:

    //! represent experiment and corresponding real data
    class KitItem {
    public:
        friend class FitSuiteKit;
        KitItem() : m_experiment(0), m_real_data(0){}
        KitItem(Experiment *experiment, const OutputData<double > *real_data) : m_experiment(experiment), m_real_data(real_data) {}
    private:
        Experiment *m_experiment;
        const OutputData<double > *m_real_data;
    };
    typedef std::vector<KitItem > KitItemVector_t;

    FitSuiteKit() {}
    virtual ~FitSuiteKit() { clear(); }

    //! clear all data
    void clear() { m_kit.clear(); }

    //! add to kit pair of (experiment, real data) for consecutive simulation
    void add(Experiment *experiment, const OutputData<double > *real_data) { m_kit.push_back(KitItem(experiment, real_data)); }

    //! loop through all defined experiments and run they simulation
    void runSimulation()
    {
        for(KitItemVector_t::iterator it = m_kit.begin(); it!= m_kit.end(); ++it) {
            (*it).m_experiment->runSimulation();
            (*it).m_experiment->normalize();
        }
    }

    //! return number of items
    size_t size() const { return m_kit.size(); }

    //! get simulated data
    const OutputData<double> * getSimulatedData(int i_item = 0) const { return m_kit[check_index(i_item)].m_experiment->getOutputData(); }

    //! get real data
    const OutputData<double> * getRealData(int i_item = 0) const { return m_kit[check_index(i_item)].m_real_data; }
    //! set real data
    void setRealData(const OutputData<double > *real_data, int i_item = 0) { m_kit[check_index(i_item)].m_real_data = real_data; }

    //! get experiment
    const Experiment *getExperiment(int i_item = 0) const { return m_kit[check_index(i_item)].m_experiment; }

private:
    //! disabled copy constructor and assignment operator
    FitSuiteKit &operator=(const FitSuiteKit &other);
    FitSuiteKit(const FitSuiteKit &other);

    //! check if index inside vector bounds
    inline size_t check_index(size_t index) const { return index < m_kit.size() ? index : throw OutOfBoundsException("FitSuiteKit::check() -> Index outside of range"); }

    KitItemVector_t m_kit; //  set of experiment and

};




#endif // FITSUITEKIT_H
