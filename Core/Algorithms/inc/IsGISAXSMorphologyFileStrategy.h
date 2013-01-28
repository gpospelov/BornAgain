#ifndef ISGISAXSMORPHOLOGYFILESTRATEGY_H_
#define ISGISAXSMORPHOLOGYFILESTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSMorphologyFileStrategy.h
//! @brief  Definition of IsGISAXSMorphologyFileStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 7, 2013

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"

//- -------------------------------------------------------------------
//! @class IsGISAXSMorphologyFileStrategy
//! @brief Definition of interference function strategy that emulates
//! the behaviour of IsGISAXS for morphology files
//- -------------------------------------------------------------------
class IsGISAXSMorphologyFileStrategy : public IInterferenceFunctionStrategy
{
public:
    IsGISAXSMorphologyFileStrategy(SimulationParameters sim_params);
    virtual ~IsGISAXSMorphologyFileStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
            const SafePointerVector<IInterferenceFunction> &ifs);
    void initPositions(const std::vector<double> &x_positions, const std::vector<double> &y_positions);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
private:
    bool checkVectorSizes();
    std::vector<double> m_x_positions;
    std::vector<double> m_y_positions;
    double m_win_x, m_win_y;
    //! Hann function
    double hannFunction(double x, double y) const;
};



#endif /* ISGISAXSMORPHOLOGYFILESTRATEGY_H_ */
