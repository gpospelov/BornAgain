#include "JobItem.h"
#include <QTimer>
#include <QDebug>


JobItem::JobItem()
    : m_progress(0)
{

}


JobItem::~JobItem()
{
    qDebug() << "JobItem::~JobItem()";
}


void JobItem::run()
{
    qDebug() << "JobItem::run() 1.1";
    loopFunctionWithDelay();
    qDebug() << "JobItem::run() 1.2 emiting finished";
}



void JobItem::loopFunctionWithDelay()
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



void JobItem::terminate()
{
    m_progress = 1000;
}
