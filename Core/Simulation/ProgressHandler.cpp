// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ProgressHandler.cpp
//! @brief     Implements class ProgressHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProgressHandler.h"
#include "MultiLayer.h"
#include "Simulation.h"
#include <mutex>

ProgressHandler::ProgressHandler()
    : m_nitems(0)
    , m_nitems_max(0)
    , m_current_progress(0)
{
}

void ProgressHandler::reset()
{
    m_nitems = 0;
    m_nitems_max = 0;
    m_current_progress = 0;
    m_callback = nullptr;
}


//! Collects number of items processed by different DWBASimulation's.
//! Calculates general progress and inform GUI if progress has changed.
//! Return flag is obtained from GUI and transferred to DWBASimulation to ask
//! them to stop calculations.
bool ProgressHandler::update(int n)
{
    static std::mutex single_mutex;
    std::unique_lock<std::mutex> single_lock( single_mutex );

    // this flag is to inform Simulation that GUI wants it to be terminated
    bool continue_calculations(true);

    m_nitems += n;

    int progress = int(double(100*m_nitems)/double(m_nitems_max)); // in percents
    //std::cout << "ProgressHandler::update n:" << n << " m_nitems:" << m_nitems <<
    //         " m_nitems_max:" << m_nitems_max << " progress:" << progress << std::endl;
    if(progress != m_current_progress) {
        m_current_progress = progress;
    }
    if(m_callback) {
        continue_calculations = m_callback(m_current_progress); // report to gui
    }

    return continue_calculations;
}


//! Initialize ProgressHandler, estimates number of items to be calculated
//! by DWBASimulation's.
void ProgressHandler::init(Simulation* simulation, int param_combinations)
{
    m_nitems = 0;
    m_current_progress = 0;
    m_nitems_max = 0;

    MultiLayer* multilayer = dynamic_cast<MultiLayer*>(simulation->getSample());

    double number_of_rounds_factor(0.0);
    int nlayouts(0);
    for(size_t i_layer=0; i_layer<multilayer->getNumberOfLayers(); ++i_layer) {
        nlayouts += multilayer->getLayer(i_layer)->getNumberOfLayouts();
    }
    if(nlayouts > 0) number_of_rounds_factor += 1.0;

    // Analyzing sample for additional factors which will slow done the simulation
    int nroughness(0);
    if(multilayer) {
        for (size_t i=0; i<multilayer->getNumberOfInterfaces(); ++i) {
            if(multilayer->getLayerInterface(i)->getRoughness() ) {
                nroughness++;
            }
        }
    }
    if(nroughness>0) number_of_rounds_factor += 1.0;

    // Simplified estimation of total number of items in DWBA simulation
    m_nitems_max = number_of_rounds_factor*param_combinations*
        simulation->getNumberOfSimulationElements();
}
