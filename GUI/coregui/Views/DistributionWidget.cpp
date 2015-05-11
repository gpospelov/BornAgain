#include "DistributionWidget.h"

namespace {
int number_of_points_for_smooth_plot = 100;
double sigmafactor_for_smooth_plot = 4;
double gap_between_bars = 0.05;

std::string noneDistribution = "DistributionNone";
}

// FIXME When first time shown (and distribution is None by default) plot is not updated. I.e.
//       it is updated first only when switched to some other distribution

// FIXME Add status label at the bottom displaying current cursor position in axes coordinates

// FIXME Distribution Gate is not working (one have to zoom around to start to see it)

// FIXME Different distributions occupies different width on the plot

// FIXME Move DistributionWidget and DistributionEditor files into Views/InfoWidgets

// FIXME distributionLorentz is shown with shifted yaxis

DistributionWidget::DistributionWidget(QWidget *parent)
    : QWidget(parent)
    , m_plot(new QCustomPlot)
    , m_item(0)
    , m_x(0)
    , m_y(0)
    , m_label(new QLabel("[x: 0,  y: 0]"))
{

    connect(m_plot, SIGNAL(mousePress(QMouseEvent *event)),
            this, SLOT(movePoint(QMouseEvent *e)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_plot,1);
    mainLayout->addWidget(m_label);
    setLayout(mainLayout);

}

void DistributionWidget::setItem(DistributionItem *item)
{
    if (m_item == item) return;

    if (m_item) {
//        disconnect(m_item, SIGNAL(propertyChanged(QString)),
//                this, SLOT(onPropertyChanged(QString)));
        disconnect();
    }

    m_item = item;

    if (!m_item) return;

    plotItem();
    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged()));
}

void DistributionWidget::plotItem()
{
    m_plot->clearGraphs();
    m_plot->clearItems();
    m_plot->clearPlottables();



    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                            QCP::iSelectLegend | QCP::iSelectPlottables);
    m_plot->xAxis->setLabel(m_item->itemName());
    m_plot->yAxis->setLabel("y");
    m_plot->xAxis2->setVisible(true);
    m_plot->yAxis2->setVisible(true);
    m_plot->xAxis2->setTickLabels(false);
    m_plot->yAxis2->setTickLabels(false);
    m_plot->xAxis2->setTicks(false);
    m_plot->yAxis2->setTicks(false);

    // FIXME use boost::scoped_ptr instead, to not to delete after
    IDistribution1D *distribution;

    // FIXME Use  Constnants::DistributionNoneType instead of your own noneDistribution
    std::cout << m_item->itemName().toStdString() << " " << noneDistribution << std::endl;

    if(m_item->itemName().toStdString() != noneDistribution) {
        distribution = m_item->createDistribution();

        // FIXME respect max length of line 100 characters
        int numberOfSamples = m_item->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
        double sigmafactor = m_item->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble();

        QVector<double> xBar;
        QVector<double> x;
        xBar = xBar.fromStdVector(distribution->generateValueList(numberOfSamples, sigmafactor));
        x = x.fromStdVector(distribution->generateValueList(number_of_points_for_smooth_plot,sigmafactor_for_smooth_plot));
        QVector<double> yBar(xBar.size());
        QVector<double> y(x.size());
        double sumOfWeigths(0);

        for(int i = 0; i < xBar.size(); ++i) {
            yBar[i] = distribution->probabilityDensity(xBar[i]);
            sumOfWeigths += yBar[i];
        }
        for(int i = 0; i < x.size(); ++i) {
            y[i] = distribution->probabilityDensity(x[i]);
        }
        for(int i = 0; i < y.size(); ++i) {
            y[i] = y[i]/sumOfWeigths;
        }
        for(int i = 0; i < yBar.size(); ++i) {
            yBar[i] = yBar[i]/sumOfWeigths;
        }

        m_plot->addGraph();
        m_plot->graph(0)->setData(x,y);
        QCPBars *bars = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars->setWidth(getWidthOfBars(xBar[0], xBar[xBar.length()-1], xBar.length()));
        bars->setData(xBar, yBar);
        // FIXME replace hard coded values with constants
        m_plot->xAxis->setRange(x[0]*0.9, x[x.size()-1]*1.1);
        m_plot->yAxis->setRange(0, y[getMaxYPosition(y.size())]*1.1);
        m_plot->addPlottable(bars);
        setVerticalDashedLine(xBar[0],0,xBar[xBar.length()-1],m_plot->yAxis->range().upper);

        delete distribution;

    }
    else {
        QVector<double> xPos;
        QVector<double> yPos;
        xPos.push_back(m_item->getRegisteredProperty(DistributionNoneItem::P_VALUE).toDouble());
        yPos.push_back(1);
        QCPBars *bars = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars->setWidth(xPos[0]/10);
        bars->setData(xPos, yPos);
        m_plot->addPlottable(bars);
        m_plot->xAxis->setRange(xPos[0]*0.9, xPos[0]*1.1);
        m_plot->yAxis->setRange(0, yPos[0]*1.1);
        setVerticalDashedLine(xPos[0],0,xPos[xPos.size()-1],m_plot->yAxis->range().upper);



    }

    m_plot->replot();
    connect(m_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));


}

void DistributionWidget::onPropertyChanged()
{
    plotItem();
}


double DistributionWidget::getWidthOfBars(double min, double max, int samples)
{
    double widthConst = (max - min)*gap_between_bars;
    double widthSample = (max - min)/samples;

    if(widthConst > widthSample) {
        return widthSample;
    }
    return widthConst;


}

void DistributionWidget::setVerticalDashedLine(double xMin, double yMin, double xMax, double yMax)
{
    QCPItemLine *min = new QCPItemLine(m_plot);
    QCPItemLine *max = new QCPItemLine(m_plot);

    QPen pen(Qt::blue, 1, Qt::DashLine);
    min->setPen(pen);
    max->setPen(pen);

    min->setSelectable(true);
    max->setSelectable(true);


    //Adding the vertical lines to the plot
    m_plot->addItem(min);
    min->start->setCoords(xMin, yMin);
    min->end->setCoords(xMin, yMax);

    m_plot->addItem(max);
    max->start->setCoords(xMax, yMin);
    max->end->setCoords(xMax, yMax);
}


int DistributionWidget::getMaxYPosition(int y)
{
    if((y-1)%2 == 0) {
        return (y-1)/2;
    }
    else {
        return (y/2)-1;
    }
}


void DistributionWidget::onMouseMove(QMouseEvent *event)
{

    QPoint point = event->pos();
    double xPos = m_plot->xAxis->pixelToCoord(point.x());
    double yPos = m_plot->yAxis->pixelToCoord(point.y());

    if(m_plot->xAxis->range().contains(xPos) && m_plot->yAxis->range().contains(yPos)) {
        m_x = xPos;
        m_y = yPos;
        std::stringstream labelText;
        labelText << "[x: " << m_x << ",  y: " << m_y << "]";
        m_label->setText(labelText.str().c_str());
    }
}
