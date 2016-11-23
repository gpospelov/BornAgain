// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DistributionWidget.cpp
//! @brief     Implements class DistributionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DistributionWidget.h"
#include "DistributionItem.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include <QLabel>
#include <QVBoxLayout>
#include <sstream>

namespace
{
int number_of_points_for_smooth_plot = 100;
double sigmafactor_for_smooth_plot = 3.5;
double gap_between_bars = 0.05;
double xRangeDivisor = 9;
double xBarRange = 0.4;
double percentage_for_yRange = 1.1;
int warning_sign_xpos = 50;
int warning_sign_ypos = 18;
}

DistributionWidget::DistributionWidget(QWidget *parent)
    : QWidget(parent)
    , m_plot(new QCustomPlot)
    , m_item(0)
    , m_label(new QLabel)
    , m_resetAction(new QAction(this))
    , m_xRange(new QCPRange)
    , m_yRange(new QCPRange)
    , m_warningSign(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_resetAction->setText("Reset View");
    connect(m_resetAction, SIGNAL(triggered()), this, SLOT(resetView()));

    m_label->setAlignment(Qt::AlignVCenter| Qt::AlignLeft);
    m_label->setStyleSheet("background-color:white;");
    m_label->setMargin(3);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_plot, 1);
    mainLayout->addWidget(m_label);
    setLayout(mainLayout);

    setStyleSheet("background-color:white;");
    connect(m_plot, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(onMousePress(QMouseEvent *)));
    connect(m_plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease(QMouseEvent*)));
    connect(m_plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease(QMouseEvent*)));
}

void DistributionWidget::setItem(DistributionItem *item)
{
    if (m_item == item) {
        return;

    } else {
        if (m_item) {
            disconnect();
            m_item->mapper()->unsubscribe(this);
        }

        m_item = item;
        if (!m_item) return;

        plotItem();

        m_item->mapper()->setOnPropertyChange(
                    [this](QString)
        {
            plotItem();
        }, this);

    }

}

void DistributionWidget::plotItem()
{
    delete m_warningSign;
    m_warningSign = 0;

    m_plot->clearGraphs();
    m_plot->clearItems();
    m_plot->clearPlottables();
    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes
                            | QCP::iSelectLegend | QCP::iSelectPlottables);
    m_plot->yAxis->setLabel("probability");
    m_plot->xAxis2->setVisible(true);
    m_plot->yAxis2->setVisible(true);
    m_plot->xAxis2->setTickLabels(false);
    m_plot->yAxis2->setTickLabels(false);
    m_plot->xAxis2->setTicks(false);
    m_plot->yAxis2->setTicks(false);

    std::unique_ptr<IDistribution1D> P_distribution {};
    bool exceptionThrown = false;
    try {
        P_distribution = m_item->createDistribution();
    } catch (const std::exception &ex) {
        exceptionThrown = true;
        Q_UNUSED(ex);
        m_plot->clearGraphs();
        m_plot->clearItems();
        m_plot->clearPlottables();

        m_warningSign = new WarningSignWidget(this);

        QString message
            = QString("Wrong parameters\n").append(QString::fromStdString(ex.what()));

        m_warningSign->setWarningMessage(message);
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(), pos.y());
        m_warningSign->show();
    }

    if (m_item->itemName() != Constants::DistributionNoneType && !exceptionThrown) {
        int numberOfSamples
            = m_item->getItemValue(DistributionItem::P_NUMBER_OF_SAMPLES).toInt();
        double sigmafactor
            = m_item->getItemValue(DistributionItem::P_SIGMA_FACTOR).toDouble();

        QVector<double> xBar;
        QVector<double> x;
        xBar = xBar.fromStdVector(P_distribution->equidistantPoints(numberOfSamples, sigmafactor));
        x = x.fromStdVector(P_distribution->equidistantPoints(number_of_points_for_smooth_plot,
                                                              sigmafactor_for_smooth_plot));
        QVector<double> yBar(xBar.size());
        QVector<double> y(x.size());
        double sumOfWeigths(0);

        for (int i = 0; i < xBar.size(); ++i) {
            yBar[i] = P_distribution->probabilityDensity(xBar[i]);
            sumOfWeigths += yBar[i];
        }
        for (int i = 0; i < x.size(); ++i) {
            y[i] = P_distribution->probabilityDensity(x[i]);
        }
        for (int i = 0; i < y.size(); ++i) {
            y[i] = y[i] / sumOfWeigths;
        }
        for (int i = 0; i < yBar.size(); ++i) {
            yBar[i] = yBar[i] / sumOfWeigths;
        }
        m_plot->addGraph();
        m_plot->graph(0)->setData(x, y);
        QCPBars *bars = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars->setWidth(getWidthOfBars(xBar[0], xBar[xBar.length() - 1], xBar.length()));
        bars->setData(xBar, yBar);
        double xRange = (x[x.size() - 1] - x[0]) / xRangeDivisor;
        m_xRange = new QCPRange(x[0] - xRange, x[x.size() - 1] + xRange);
        m_yRange = new QCPRange(0, y[getMaxYPosition(y.size())] * percentage_for_yRange);
        m_plot->xAxis->setRange(*m_xRange);
        m_plot->yAxis->setRange(*m_yRange);
        m_plot->addPlottable(bars);
        setVerticalDashedLine(xBar[0], 0, xBar[xBar.length() - 1], m_plot->yAxis->range().upper);
    } else if(!exceptionThrown) {
        QVector<double> xPos;
        QVector<double> yPos;
        xPos.push_back(m_item->getItemValue(DistributionNoneItem::P_VALUE).toDouble());
        yPos.push_back(1);
        QCPBars *bars = new QCPBars(m_plot->xAxis, m_plot->yAxis);
        bars->setWidth(gap_between_bars);
        bars->setData(xPos, yPos);
        m_plot->addPlottable(bars);
        m_xRange = new QCPRange(xPos[0] - xBarRange, xPos[0] + xBarRange);
        m_yRange = new QCPRange(0, yPos[0] * percentage_for_yRange);
        m_plot->xAxis->setRange(*m_xRange);
        m_plot->yAxis->setRange(*m_yRange);
        setVerticalDashedLine(xPos[0], 0, xPos[xPos.size() - 1], m_plot->yAxis->range().upper);
    }
    m_plot->replot();
    connect(m_plot, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(onMouseMove(QMouseEvent *)));
}

double DistributionWidget::getWidthOfBars(double min, double max, int samples)
{
    double widthConst = (max - min) * gap_between_bars;
    double widthSample = (max - min) / samples;

    if (widthConst > widthSample) {
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

    // Adding the vertical lines to the plot
    m_plot->addItem(min);
    min->start->setCoords(xMin, yMin);
    min->end->setCoords(xMin, yMax);

    m_plot->addItem(max);
    max->start->setCoords(xMax, yMin);
    max->end->setCoords(xMax, yMax);
}

int DistributionWidget::getMaxYPosition(int y)
{
    if ((y - 1) % 2 == 0) {
        return (y - 1) / 2;
    } else {
        return (y / 2) - 1;
    }
}

// get current mouse position in plot
void DistributionWidget::onMouseMove(QMouseEvent *event)
{
    QPoint point = event->pos();
    double xPos = m_plot->xAxis->pixelToCoord(point.x());
    double yPos = m_plot->yAxis->pixelToCoord(point.y());

    if (m_plot->xAxis->range().contains(xPos) && m_plot->yAxis->range().contains(yPos)) {
        std::stringstream labelText;
        labelText << "[x: " << xPos << ",  y: " << yPos << "]";
        m_label->setText(labelText.str().c_str());
    }
}

void DistributionWidget::onMousePress(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QPoint point = event->globalPos();
        QMenu menu;
        menu.addAction(m_resetAction);
        menu.exec(point);
    }
}

void DistributionWidget::resetView()
{
    m_plot->xAxis->setRange(*m_xRange);
    m_plot->yAxis->setRange(*m_yRange);
    m_plot->replot();
}

void DistributionWidget::setXAxisName(QString xAxisName)
{
    m_plot->xAxis->setLabel(xAxisName);
}

//! Returns position for warning sign at the bottom right corner of the editor. The position will
//! be adjusted according to the visibility of scroll bars
QPoint DistributionWidget::getPositionForWarningSign()
{
    int x = m_plot->geometry().topRight().x() - warning_sign_xpos;
    int y = m_plot->geometry().topRight().y() + warning_sign_ypos;
    return QPoint(x, y);
}

//! adjusts position of warning label on widget move
void DistributionWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if (m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(), pos.y());
    }
}
