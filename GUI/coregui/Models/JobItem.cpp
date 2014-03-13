#include "JobItem.h"
#include <QTimer>
#include <QDebug>


JobItem::JobItem()
    : m_counterForDelayedLoop(0)
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
    qDebug() << "JobItem::loopFunctionWithDelay()" << m_counterForDelayedLoop;
    if(m_counterForDelayedLoop < 100) {
        m_counterForDelayedLoop++;
        qDebug() << "XXX1";
        QTimer::singleShot(500, this, SLOT(loopFunctionWithDelay()));
        qDebug() << "XXX2";
    }

    if(m_counterForDelayedLoop == 100) emit finished();
}


