#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include "DistributionPlotwidget.h"

DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_mainLayout(new QHBoxLayout)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    BeamWavelengthItem *item = new BeamWavelengthItem;

    DistributionItem *item = new DistributionGaussianItem;
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

    plotItem(m_item);

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


    DistributionGaussianItem *gausItem = dynamic_cast<DistributionGaussianItem *>(m_item);
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
//    plot->xAxis->setRange(x[0], x[(x.size()-1)]);
//    plot->yAxis->setRange(-1, 1);
    QCPBars *bars1 = new QCPBars(m_plot->xAxis, m_plot->yAxis);
    bars1->setWidth(0.1/x.size());
    bars1->setData(x, y);
    m_plot->addPlottable(bars1);
    m_plot->rescaleAxes();
    m_plot->replot();
//    m_mainLayout->addWidget(plot,1);




}

void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
//    DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
//    Q_ASSERT(distrItem);

//    qDebug() << "TestView::onSubItemChanged() ->" << property_name << distrItem->modelType();

}

void DistributionEditor::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";

    qDebug() <<  "          " "TestView::onPropertyChanged(const QString &property_name) ->" << property_group << property_name;

}



