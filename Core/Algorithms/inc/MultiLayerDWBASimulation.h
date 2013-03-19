// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/MultiLayerDWBASimulation.h 
//! @brief     Defines class MultiLayerDWBASimulation.
//
// ************************************************************************** //

#ifndef MULTILAYERDWBASIMULATION_H_
#define MULTILAYERDWBASIMULATION_H_

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

    virtual void init(const Simulation &simulation);

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
