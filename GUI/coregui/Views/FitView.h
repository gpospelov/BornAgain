#ifndef FITMANAGER_H
#define FITMANAGER_H

#include <QWidget>
#include "qcustomplot.h"

class FitView : public QWidget
{
    Q_OBJECT

public:
    FitView(QWidget *parent = 0);
    virtual ~FitView(){}

    QCustomPlot *m_customPlot;
};


#endif // FITMANAGER_H
