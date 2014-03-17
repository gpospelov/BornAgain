#include "JobRunner.h"
#include "Simulation.h"
#include <QTimer>
#include <QDebug>


JobRunner::JobRunner(QString identifier)
    : m_identifier(identifier)
    , m_progress(0)
{

}


JobRunner::~JobRunner()
{
    qDebug() << "JobRunner::~JobRunner()";
}


void JobRunner::start()
{
    qDebug() << "JobRunner::start() 1.1";
    emit started();
    loopFunctionWithDelay();
}



void JobRunner::loopFunctionWithDelay()
{
    qDebug() << "JobItem::loopFunctionWithDelay()" << m_progress;
    if(m_progress < 100) {
        m_progress = m_progress+4;
        emit progressUpdate();
        QTimer::singleShot(500, this, SLOT(loopFunctionWithDelay()));
    }

    if(m_progress >= 100) {
        qDebug() << "JobRunner::loopFunctionWithDelay() 1.1";
        emit progressUpdate();
        qDebug() << "JobRunner::loopFunctionWithDelay() 1.2";
        emit finished();
        qDebug() << "JobRunner::loopFunctionWithDelay() 1.3";
    }
}



void JobRunner::terminate()
{
    m_progress = 1000;
}
