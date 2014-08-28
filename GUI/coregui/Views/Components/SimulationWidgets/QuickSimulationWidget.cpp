#include "QuickSimulationWidget.h"
#include "QuickSimulationSettings.h"
#include "ModelTuningWidget.h"
#include "OutputDataWidget.h"
#include "QuickSimulationRunner.h"
#include "OutputDataWidget.h"
#include "minisplitter.h"

#include "qdebug.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include <QSplitter>



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

    m_outputDataWidget = new OutputDataWidget(this, false, false);

    m_quickSimulationRunner = new QuickSimulationRunner(this);
    m_quickSimulationRunner->setOutputDataWidget(m_outputDataWidget);


    m_modelTuningWidget = new ModelTuningWidget(m_sampleModel, m_instrumentModel);
    m_modelTuningWidget->setQuickSimulationRunner(m_quickSimulationRunner);
    //m_modelTuningWidget->setFixedWidth(320);
    m_modelTuningWidget->setContentsMargins(0,0,0,0);

    m_quickSimulationSettings = new QuickSimulationSettings();


    QVBoxLayout *settingsLayout = new QVBoxLayout(this);
    settingsLayout->addWidget(m_quickSimulationSettings);
    settingsLayout->addWidget(m_modelTuningWidget);
    settingsLayout->setMargin(0);
    settingsLayout->setSpacing(0);

    QWidget *settingsWidget = new QWidget();
    settingsWidget->setLayout(settingsLayout);


    m_splitter = new Manhattan::MiniSplitter(this);
    m_splitter->setStyleSheet("background-color:white;");
    m_splitter->addWidget(m_outputDataWidget);
    m_splitter->addWidget(settingsWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_splitter);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    connect(m_quickSimulationSettings, SIGNAL(sliderRangeFactorChanged(double)), this, SLOT(sliderRangeChanged(double)));

}

void QuickSimulationWidget::updateViews(const QString &instrument, const QString &sample)
{
    m_modelTuningWidget->updateTreeView(instrument, sample);
}

void QuickSimulationWidget::sliderRangeChanged(double value)
{
    //qDebug() << "QuickSimulationWidget::sliderRangeChanged" << value;
    m_modelTuningWidget->setSliderRangeFactor(value);
}








