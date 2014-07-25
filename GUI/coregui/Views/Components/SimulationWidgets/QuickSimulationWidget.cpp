#include "QuickSimulationWidget.h"
#include "qdebug.h"
#include "QHBoxLayout"
#include "SampleTuningWidget.h"
#include "PlotWidget.h"


QuickSimulationWidget::QuickSimulationWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent)
    : QWidget(parent)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
{

    QColor bgColor(0,0,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    //setPalette(palette);

    m_plotWidget = new PlotWidget(false);
    m_plotWidget->setObjectName(QString::fromUtf8("OutputDataWidget::customPlot"));
    m_plotWidget->setProjectionsVisible(false);
    m_plotWidget->setPropertyPanelVisible(false);
    //m_plotWidget->setFixedWidth(600);

    m_sampleTuningWidget = new SampleTuningWidget(m_sampleModel, m_instrumentModel);
    m_sampleTuningWidget->setFixedWidth(380);
    m_sampleTuningWidget->setContentsMargins(0,0,0,0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_plotWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(m_sampleTuningWidget);

    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);
}

void QuickSimulationWidget::updateViews()
{
    m_sampleTuningWidget->updateTreeView();
}








