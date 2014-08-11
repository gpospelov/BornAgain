#include "QuickSimulationWidget.h"
#include "qdebug.h"
#include "QHBoxLayout"
#include "ModelTuningWidget.h"
#include "OutputDataWidget.h"
#include "QuickSimulationRunner.h"
#include "OutputDataWidget.h"


QuickSimulationWidget::QuickSimulationWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent)
    : QWidget(parent)
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
    , m_quickSimulationRunner(0)
{

    QColor bgColor(0,0,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    //setPalette(palette);

    m_outputDataWidget = new OutputDataWidget(this, false);
    m_outputDataWidget->setPropertyPanelVisible(false);
    //m_plotWidget->setProjectionsVisible(false);
    //m_plotWidget->setPropertyPanelVisible(false);
    //m_plotWidget->setFixedWidth(600);


    m_quickSimulationRunner = new QuickSimulationRunner(this);
    m_quickSimulationRunner->setOutputDataWidget(m_outputDataWidget);


    m_modelTuningWidget = new ModelTuningWidget(m_sampleModel, m_instrumentModel);
    m_modelTuningWidget->setQuickSimulationRunner(m_quickSimulationRunner);
    m_modelTuningWidget->setFixedWidth(320);
    //m_modelTuningWidget->setFixedHeight(800);
    m_modelTuningWidget->setContentsMargins(0,0,0,0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_outputDataWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(m_modelTuningWidget);

    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);

}

void QuickSimulationWidget::updateViews(const QString &instrument, const QString &sample)
{
    m_modelTuningWidget->updateTreeView(instrument, sample);
}








