// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataCanvas.cpp
//! @brief     Implements class SpecularDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AppSvc.h"
#include "ColorMapUtils.h"
#include "projectmanager.h"
#include "SavePlotAssistant.h"
#include "SpecularDataCanvas.h"
#include "SpecularDataItem.h"
#include "plot_constants.h"

SpecularDataCanvas::SpecularDataCanvas(QWidget* parent)
    : SessionItemWidget(parent)
    , m_customPlot(new QCustomPlot)
    , m_resetViewAction(nullptr)
    , m_savePlotAction(nullptr)

{
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addWidget(m_customPlot);
    setLayout(vlayout);
    setStyleSheet("background-color:white;");

    initGraph();

    m_customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));
    m_customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), Constants::plot_tick_label_size));

    ColorMapUtils::setLogz(m_customPlot->yAxis, true);

    m_customPlot->xAxis->setLabel("iteration");
    m_customPlot->yAxis->setLabel("chi2");

    m_customPlot->xAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));
    m_customPlot->yAxis->setLabelFont(QFont(QFont().family(), Constants::plot_axes_label_size));

    initActions();

    connect(m_customPlot, &QCustomPlot::mousePress, this,
            &SpecularDataCanvas::onMousePress, Qt::UniqueConnection);
}

void SpecularDataCanvas::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    initGraphFromItem();
}

QSize SpecularDataCanvas::sizeHint() const { return QSize(500, 400); }

QSize SpecularDataCanvas::minimumSizeHint() const { return QSize(128, 128); }

QList<QAction*> SpecularDataCanvas::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_savePlotAction;
}

void SpecularDataCanvas::onResetViewAction() { specularDataItem()->resetView(); }

void SpecularDataCanvas::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_customPlot, specularDataItem()->getOutputData());
}

void SpecularDataCanvas::onMousePress(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
        emit customContextMenuRequested(event->globalPos());
}

/*void SpecularDataCanvas::clearData()
{
    m_customPlot->removeGraph(m_customPlot->graph());
    initGraph();
    m_customPlot->replot();
}*/

void SpecularDataCanvas::initGraph()
{
    m_customPlot->addGraph();

    QPen pen(QColor(0, 0, 255, 200));
    m_customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    m_customPlot->graph()->setPen(pen);

    QFontMetrics fontMetric(font());
    auto em = fontMetric.width('M'), fontAscent = fontMetric.ascent();
    auto* axisRectangle = m_customPlot->axisRect();
    axisRectangle->setAutoMargins(QCP::msTop | QCP::msBottom);
    axisRectangle->setMargins(QMargins(em*4, fontAscent*2, em*2, fontAscent*2));
}

void SpecularDataCanvas::initGraphFromItem()
{
    const auto underlying_data = specularDataItem()->getOutputData();
    for (size_t i = 0, size = underlying_data->getAllocatedSize(); i < size; ++i) {
        double x = underlying_data->getAxisValue(i, 0);
        double y = underlying_data->operator[](i);
        m_customPlot->graph()->addData(x, y);
    }
}

SpecularDataItem* SpecularDataCanvas::specularDataItem()
{
    SpecularDataItem* result = dynamic_cast<SpecularDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

// TODO: try to reuse IntensityDataCanvas::initActions somehow
void SpecularDataCanvas::initActions()
{
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset view\n"
                                  "x,y,z axes range will be set to default");
    connect(m_resetViewAction, &QAction::triggered, this, &SpecularDataCanvas::onResetViewAction);

    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save");
    m_savePlotAction->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_savePlotAction->setToolTip("Save plot");
    connect(m_savePlotAction, &QAction::triggered, this, &SpecularDataCanvas::onSavePlotAction);
}
