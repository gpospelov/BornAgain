#include "ProgressHandlerDWBA.h"

ProgressHandlerDWBA::ProgressHandlerDWBA()
    : m_nitems(0)
    , m_nitems_total(0)
    , m_report_every_nth(100)
{

}


//! Method increments number of items processed.
//! Every n'th processed item the Simulation is informed via thread safe callback.
//! Return flag false is used to inform DWBSimulation to interrupt calculations.
bool ProgressHandlerDWBA::update()
{
    bool continue_calculations(true);
    if(!m_callback) {
        return continue_calculations;
    }

    m_nitems_total++;
    m_nitems++;
    if(m_nitems == m_report_every_nth) {
        continue_calculations = m_callback(m_nitems); // report to the Simulation
        m_nitems=0;
    }
    return continue_calculations;
}


bool ProgressHandlerDWBA::finished()
{
    if(m_callback) {
        m_callback(m_nitems); // report to the Simulation
        m_nitems = 0;
    }
    return true;
}


