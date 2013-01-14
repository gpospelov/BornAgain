#ifndef MULTILAYERDWBASIMULATION_H_
#define MULTILAYERDWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MultiLayerDWBASimulation.h
//! @brief  Definition of MultiLayerDWBASimulation class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 26, 2012

#include "LayerDWBASimulation.h"

#include <set>
#include <map>

class MultiLayer;
class MultiLayerRoughnessDWBASimulation;


class MultiLayerDWBASimulation : public DWBASimulation
{
public:
    MultiLayerDWBASimulation(const MultiLayer *p_multi_layer);
    virtual ~MultiLayerDWBASimulation();

    MultiLayerDWBASimulation *clone() const { throw NotImplementedException("MultiLayerDWBASimulation::clone() -> Error: not implemented"); }

    virtual void init(const Experiment &experiment);

    //! Set thread information for masking
    virtual void setThreadInfo(const ThreadInfo &thread_info);

    virtual void run();
protected:
    std::set<double> getAlphaList() const;
    std::map<size_t, LayerDWBASimulation*> m_layer_dwba_simulation_map;
    MultiLayer *mp_multi_layer;
    MultiLayerRoughnessDWBASimulation *mp_roughness_dwba_simulation;
};


#endif /* MULTILAYERDWBASIMULATION_H_ */
