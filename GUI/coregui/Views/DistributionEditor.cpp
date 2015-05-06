#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include "DistributionPlotwidget.h"
#include <iostream>

DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_mainLayout(new QHBoxLayout)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    BeamWavelengthItem *item = new BeamWavelengthItem;

//    DistributionItem *item = new DistributionGaussianItem;
    DistributionPlotWidget *plotwidget = new DistributionPlotWidget;
    m_plot = plotwidget->getPlot();

    m_propertyEditor = new AwesomePropertyEditor(this);

// main layout
//    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_mainLayout->addWidget(m_propertyEditor);
    setItem(item);
    m_mainLayout->addWidget(m_plot,1);
    setLayout(m_mainLayout);


}



void DistributionEditor::setItem(ParameterizedItem *item)
{
    m_propertyEditor->setItem(item);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));
        disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                this, SLOT(onSubItemPropertyChanged(QString,QString)));
    }

    m_item = item;

    if (!m_item) return;

//    plotItem(m_item);

    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(onSubItemChanged(QString)));
    connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
            this, SLOT(onSubItemPropertyChanged(QString,QString)));

}

void DistributionEditor::plotItem(ParameterizedItem *item)
{

    DistributionGaussianItem *gausItem = dynamic_cast<DistributionGaussianItem *>(item);
    Q_ASSERT(gausItem);

    DistributionGaussian *gaus = dynamic_cast<DistributionGaussian *>(gausItem->createDistribution());
    Q_ASSERT(gaus);

    qDebug() << "TestView::plotItem(ParameterizedItem *item) ->" << gausItem->modelType();
    qDebug() << gausItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt()
             << gausItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble()
             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble()
             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_STD_DEV).toDouble()
              << gaus->getMean()
              << gaus->getStdDev();
}

void DistributionEditor::onPropertyChanged(const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
//    qDebug() << "TestView::onPropertyChanged(const QString &property_name) ->"
//             << property_name << m_item->getRegisteredProperty(property_name).toDouble();


    DistributionItem *gausItem = dynamic_cast<DistributionItem *>(m_item);
    Q_ASSERT(gausItem);

        int numberOfSamples = gausItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
        double sigmafactor = gausItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();

    DistributionGaussian *gaus = dynamic_cast<DistributionGaussian *>(gausItem->createDistribution());
    Q_ASSERT(gaus);

    qDebug() << "TestView::plotItem(ParameterizedItem *item) ->" << gausItem->modelType();
    qDebug() << gausItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt()
             << gausItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble()
             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble()
             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_STD_DEV).toDouble()
              << gaus->getMean()
              << gaus->getStdDev();
    QVector<double> x;
    x = x.fromStdVector(gaus->generateValueList(numberOfSamples, sigmafactor));
    QVector<double> y(x.size());
    for(int i = 0; i < x.size(); ++i) {
        y[i] = gaus->probabilityDensity(x[i]);
    }

    m_plot->clearGraphs();
    m_plot->removePlottable(0);
    m_plot->addGraph();
    m_plot->graph(0)->setData(x,y);
    m_plot->xAxis->setLabel("x");
    m_plot->yAxis->setLabel("y");
    QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
    bars1->setWidth(0.1/x.size());
    bars1->setData(x, y);
    m_plot->addPlottable(bars1);
    m_plot->rescaleAxes();
    m_plot->replot();

        std::cout << property_name.toStdString() << " " << std::endl;
}

void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
    m_distribution = distrItem;
    Q_ASSERT(distrItem);


//    std::cout << distrItem->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() << std::endl;
//*/    qDebug() << "TestView::onSubItemChanged() ->" << property_name << distrItem->modelType();*/
//        std::cout << property_name.toStdString() << std::endl;
}

void DistributionEditor::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";

    std::cout << property_group.toStdString() << " " << property_name.toStdString() << " "  << " " << std::endl;
    qDebug() << "TestView::onPropertyChanged(const QString &property_name) ->" << property_group << property_name;;

    std::cout << m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() <<  std::endl;

//    DistributionItem *gausItem = dynamic_cast<DistributionItem *>(m_item);
//    Q_ASSERT(gausItem);

//        int numberOfSamples = m_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
//        double sigmafactor = m_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();

    //    DistributionGaussian *gaus = dynamic_cast<DistributionGaussian *>(gausItem->createDistribution());
    //    Q_ASSERT(gaus);

    //    qDebug() << "TestView::plotItem(ParameterizedItem *item) ->" << gausItem->modelType();
    //    qDebug() << gausItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt()
    //             << gausItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble()
    //             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble()
    //             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_STD_DEV).toDouble()
    //              << gaus->getMean()
    //              << gaus->getStdDev();


    m_plot->clearGraphs();
    m_plot->removePlottable(0);

    int numberOfSamples = m_distribution->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
    double sigmafactor = m_distribution->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();
    if(m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() == "DistributionGaussian")
    {
        m_gaussian = dynamic_cast<DistributionGaussian *>(m_distribution->createDistribution());
        QVector<double> x;
        x = x.fromStdVector(m_gaussian->generateValueList(numberOfSamples, sigmafactor));
        QVector<double> y(x.size());
        for(int i = 0; i < x.size(); ++i) {
            y[i] = m_gaussian->probabilityDensity(x[i]);
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        m_plot->xAxis->setLabel("x");
        m_plot->yAxis->setLabel("y");
        QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars1->setWidth(0.1/x.size());
        bars1->setData(x, y);
        m_plot->addPlottable(bars1);
        m_plot->rescaleAxes();
        m_plot->replot();

    }
    else if(m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() == "DistributionCosine")
    {
        m_cosine = dynamic_cast<DistributionCosine *>(m_distribution->createDistribution());
        QVector<double> x;
        x = x.fromStdVector(m_cosine->generateValueList(numberOfSamples, sigmafactor));
        QVector<double> y(x.size());
        for(int i = 0; i < x.size(); ++i) {
            y[i] = m_cosine->probabilityDensity(x[i]);
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        m_plot->xAxis->setLabel("x");
        m_plot->yAxis->setLabel("y");
        QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars1->setWidth(0.1/x.size());
        bars1->setData(x, y);
        m_plot->addPlottable(bars1);
        m_plot->rescaleAxes();
        m_plot->replot();

    }
    else if(m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() == "DistributionGate")
    {
        m_gate = dynamic_cast<DistributionGate *>(m_distribution->createDistribution());
        QVector<double> x;
        x = x.fromStdVector(m_gate->generateValueList(numberOfSamples, sigmafactor));
        QVector<double> y(x.size());
        for(int i = 0; i < x.size(); ++i) {
            y[i] = m_gate->probabilityDensity(x[i]);
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        m_plot->xAxis->setLabel("x");
        m_plot->yAxis->setLabel("y");
        QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars1->setWidth(0.1/x.size());
        bars1->setData(x, y);
        m_plot->addPlottable(bars1);
        m_plot->rescaleAxes();
        m_plot->replot();

    }
    else if(m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() == "DistributionLogNormal")
    {
        m_logNormal = dynamic_cast<DistributionLogNormal *>(m_distribution->createDistribution());
        QVector<double> x;
        x = x.fromStdVector(m_logNormal->generateValueList(numberOfSamples, sigmafactor));
        QVector<double> y(x.size());
        for(int i = 0; i < x.size(); ++i) {
            y[i] = m_logNormal->probabilityDensity(x[i]);
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        m_plot->xAxis->setLabel("x");
        m_plot->yAxis->setLabel("y");
        QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars1->setWidth(0.1/x.size());
        bars1->setData(x, y);
        m_plot->addPlottable(bars1);
        m_plot->rescaleAxes();
        m_plot->replot();

    }
    else if(m_distribution->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() == "DistributionLorentz")
    {
        m_lorentz = dynamic_cast<DistributionLorentz *>(m_distribution->createDistribution());
        QVector<double> x;
        x = x.fromStdVector(m_lorentz ->generateValueList(numberOfSamples, sigmafactor));
        QVector<double> y(x.size());
        for(int i = 0; i < x.size(); ++i) {
            y[i] = m_lorentz->probabilityDensity(x[i]);
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        m_plot->xAxis->setLabel("x");
        m_plot->yAxis->setLabel("y");
        QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars1->setWidth(0.1/x.size());
        bars1->setData(x, y);
        m_plot->addPlottable(bars1);
        m_plot->rescaleAxes();
        m_plot->replot();

    }

}




