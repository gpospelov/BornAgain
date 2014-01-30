#ifndef CUSTOMCANVAS_H
#define CUSTOMCANVAS_H

#include <QWidget>
#include "qcustomplot.h"
#include "OutputData.h"

class ICanvas: public QWidget
{
    Q_OBJECT

public:
    explicit ICanvas(QWidget *parent = 0) : QWidget(parent){}
    virtual ~ICanvas(){}
    virtual void Draw(const OutputData<double> *data){}
};


class CustomCanvas : public ICanvas
{
    Q_OBJECT

public:
    explicit CustomCanvas(QWidget *parent = 0);
    virtual ~CustomCanvas(){}

    virtual void Draw(const OutputData<double> *data);

private:
    QCustomPlot *m_customPlot;
    const OutputData<double> *m_data;

};


#endif

