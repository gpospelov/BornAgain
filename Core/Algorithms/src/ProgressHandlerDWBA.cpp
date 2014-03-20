#include "ProgressHandlerDWBA.h"

ProgressHandlerDWBA::ProgressHandlerDWBA()
    : m_nitems(0)
    , m_nitems_total(0)
    , m_report_every_nth(100)
{

}


void ProgressHandlerDWBA::update()
{
    if(!m_callback) {
        std::cout << "DWBAProgressHandler::update() -> No callback" << std::endl;
        return;
    }

    m_nitems_total++;
    m_nitems++;
    if(m_nitems == m_report_every_nth) {
        m_callback(m_nitems); // report to the Simulation
        m_nitems=0;
    }
}


void ProgressHandlerDWBA::finished()
{
    if(m_callback) {
        m_callback(m_nitems); // report to the Simulation
        m_nitems = 0;
    }
}


