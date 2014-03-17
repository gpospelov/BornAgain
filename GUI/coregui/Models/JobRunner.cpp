#include "JobRunner.h"
#include "Simulation.h"
#include <QTimer>
#include <QDebug>


JobRunner::JobRunner(Simulation *simulation)
    : m_simulation(simulation)
    ,  m_progress(0)
{

}


JobRunner::~JobRunner()
{

}


void JobRunner::run()
{
    qDebug() << "JobItem::run() 1.1";
    loopFunctionWithDelay();
    qDebug() << "JobItem::run() 1.2 emiting finished";
}



void JobRunner::loopFunctionWithDelay()
{
    qDebug() << "JobItem::loopFunctionWithDelay()" << m_progress;
    if(m_progress < 100) {
        m_progress++;
        emit progressUpdate(m_progress);
        QTimer::singleShot(500, this, SLOT(loopFunctionWithDelay()));
    }

    if(m_progress == 100) {
        emit progressUpdate(m_progress);
        emit finished();
    }
}



void JobRunner::terminate()
{
    m_progress = 1000;
}
