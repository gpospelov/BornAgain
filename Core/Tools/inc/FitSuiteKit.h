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
#include "ChiSquaredModule.h"

#include <vector>


//- -------------------------------------------------------------------
//! @class FitSuiteKit
//! @brief Class containing vector of pairs  (experiment, real data) for fit and chi2 module.
//- -------------------------------------------------------------------
class FitSuiteKit
{
public:

    //! represent experiment, corresponding real data and chi2 module to calculate the difference
    class KitItem {
    public:
        KitItem(Experiment *experiment, const OutputData<double > *real_data, const IChiSquaredModule *chi2_module);
        ~KitItem();
        friend class FitSuiteKit;
        void setRealData(const OutputData<double > *real_data);
    private:
        KitItem(const KitItem &);
        KitItem &operator=(const KitItem &);
        Experiment *m_experiment; //! external experiment (not owned by this)
        OutputData<double > *m_real_data; //! real data
        IChiSquaredModule *m_chi2_module; //! chi2 module
    };
    typedef std::vector<KitItem *> KitItemVector_t;

    FitSuiteKit(){}
    virtual ~FitSuiteKit(){}

    //! clear all data
    void clear();

    //! return number of items
    size_t size() const { return m_kit.size(); }

    //! add to kit pair of (experiment, real data) for consecutive simulation and chi2 module
    void add(Experiment *experiment, const OutputData<double > *real_data, const IChiSquaredModule *chi2_module);

    //! loop through all defined experiments and run they simulation
    void runSimulation();

    //! get chi squared value calculated for all pairs of (experiment, real data)
    double getChiSquaredValue();

    //! get experiment
    const Experiment *getExperiment(int i_item = 0) const { return m_kit[check_index(i_item)]->m_experiment; }

    //! get real data
    const OutputData<double> * getRealData(int i_item = 0) const { return m_kit[check_index(i_item)]->m_real_data; }
    //! set real data
    void setRealData(const OutputData<double > *real_data, int i_item = 0) { m_kit[check_index(i_item)]->setRealData(real_data);}

    //! get chi2 module
    const IChiSquaredModule *getChiSquaredModule(int i_item = 0) const { return m_kit[check_index(i_item)]->m_chi2_module; }
    IChiSquaredModule *getChiSquaredModule(int i_item = 0) { return m_kit[check_index(i_item)]->m_chi2_module; }

    //! get simulated data
    const OutputData<double> * getSimulatedData(int i_item = 0) const { return m_kit[check_index(i_item)]->m_experiment->getOutputData(); }

private:
    //! disabled copy constructor and assignment operator
    FitSuiteKit &operator=(const FitSuiteKit &);
    FitSuiteKit(const FitSuiteKit &);

    //! check if index inside vector bounds
    inline size_t check_index(size_t index) const { return index < m_kit.size() ? index : throw OutOfBoundsException("FitSuiteKit::check() -> Index outside of range"); }

    KitItemVector_t m_kit; //  set of experiments and corresponding real data
};




#endif // FITSUITEKIT_H
