// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.cpp
//! @brief     Implements class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RunFitWidget.h"
#include "RunFitManager.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "FitSuite.h"
#include "GUIFitObserver.h"
#include "FitProgressWidget.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "FitModel.h"
#include "DomainSimulationBuilder.h"
#include "FitParameterItems.h"
#include "ParameterizedItem.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "SessionModel.h"
#include "IntensityDataIOFactory.h"
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QDebug>

RunFitWidget::RunFitWidget(FitModel *fit, SampleModel *sample, InstrumentModel *inst, QWidget *parent)
    : QWidget(parent)
  , m_start_button(0)
  , m_stop_button(0)
  , m_interval_label(0)
  , m_interval_slider(0)
  , m_runfitmanager(new RunFitManager(this))
  , m_fitprogress(new FitProgressWidget(this))
    , m_fitModel(fit)
    , m_sampleModel(sample)
    , m_instrumentModel(inst)
{
    // setup ui
    m_start_button  = new QPushButton();
    m_start_button->setText(tr("Start"));
    m_stop_button = new QPushButton();
    m_stop_button->setText(tr("Stop"));
    m_stop_button->setEnabled(false);
    m_interval_label = new QLabel();
    m_interval_slider = new QSlider();
    m_interval_slider->setOrientation(Qt::Horizontal);
    m_interval_slider->setRange(1,20);
    m_interval_slider->setMaximumWidth(150);
    m_interval_slider->setMinimumWidth(150);
    m_interval_slider->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_start_button);
    topLayout->addWidget(m_stop_button);
    topLayout->addStretch();
    topLayout->addWidget(m_interval_label);
    topLayout->addWidget(m_interval_slider);
    QWidget *topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(m_fitprogress);

    // connect everything
    connect(m_start_button, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(m_stop_button, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(m_runfitmanager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_runfitmanager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));

    connect(m_interval_slider, SIGNAL(valueChanged(int)), this, SLOT(onIntervalChanged(int)));
    connect(m_interval_slider, SIGNAL(valueChanged(int)),
                m_fitprogress->getObserver().get(), SLOT(setInterval(int)));

    setLayout(mainLayout);
    m_interval_slider->setValue(10);
}

void RunFitWidget::onIntervalChanged(int value)
{
    m_interval_label->setText(QString("Update every %1th iteration").arg(value));
}

void RunFitWidget::onStartClicked()
{
    // used for test purposes
    boost::shared_ptr<FitSuite> suite = init_test_fitsuite();
    suite->attachObserver(m_fitprogress->getObserver());

    m_runfitmanager->setFitSuite(suite);
    m_runfitmanager->runFitting();
}

void RunFitWidget::onStopClicked()
{
    m_runfitmanager->interruptFitting();
}

void RunFitWidget::onFittingStarted()
{
    m_start_button->setEnabled(false);
    m_stop_button->setEnabled(true);
}

void RunFitWidget::onFittingFinished()
{
    m_stop_button->setEnabled(false);
    m_start_button->setEnabled(true);
}



// test only
boost::shared_ptr<FitSuite> RunFitWidget::init_test_fitsuite()
{
    ParameterizedItem *multilayer = getTopItemFromSelection(m_sampleModel, Constants::MultiLayerType,
                                                            FitSelectionItem::P_SAMPLE_INDEX);
    ParameterizedItem *instrument = getTopItemFromSelection(m_instrumentModel,
                                                            Constants::InstrumentType,
                                                            FitSelectionItem::P_INSTRUMENT_INDEX);

    DomainSimulationBuilder builder;

    boost::scoped_ptr<GISASSimulation> simulation(builder.getSimulation(dynamic_cast<MultiLayerItem*>
                                                                          (multilayer),
                                                                          dynamic_cast<InstrumentItem*>
                                                                          (instrument)));
    QFileInfo checkFile(path);

    OutputData<double> *data = 0;

    if (checkFile.exists()) {
        data = IntensityDataIOFactory::readOutputData(path.toStdString());
        qDebug() << data->totalSum();
        //Q_ASSERT(0);
    } else {

        simulation->runSimulation();
        data = simulation->getOutputData()->clone();
    }


    boost::shared_ptr<FitSuite> m_fitsuite = boost::shared_ptr<FitSuite>(new FitSuite());


    m_fitsuite->addSimulationAndRealData(*simulation.get(), *data);


    ParameterizedItem *container =m_fitModel->itemForIndex(QModelIndex())->getChildOfType(Constants::FitParameterContainerType);

    QModelIndex c_index = m_fitModel->indexOfItem(container);
    for (int i = 0; i < m_fitModel->rowCount(c_index); i++) {
        QModelIndex child = m_fitModel->index(i,0,c_index);
        ParameterizedItem *parameter = m_fitModel->itemForIndex(child);
        for (int j = 0; j < m_fitModel->rowCount(child); j++) {
            ParameterizedItem *link = m_fitModel->itemForIndex(m_fitModel->index(j,0,child));
            QString value = link->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
            value = value.replace("Position Offset/X", "PositionX");
            value = value.replace("Position Offset/Y", "PositionY");
            value = value.replace("Position Offset/Z", "PositionZ");
            value = value.replace("Rotation/ZRotation", "ZRotation");
            value = value.replace("Wavelength/DistributionNone/Value", "Wavelength");
            value = value.replace(" ", "");
            std::string translated = "*" + value.toStdString();
            std::cout << translated;
            std::cout.flush();
            double min = parameter->getRegisteredProperty(FitParameterItem::P_MIN).toDouble();
            double max = parameter->getRegisteredProperty(FitParameterItem::P_MAX).toDouble();
            double init = parameter->getRegisteredProperty(FitParameterItem::P_INIT).toDouble();
            AttLimits limits;
            if (min==max && min < init) {
                limits = AttLimits::lowerLimited(min);
            } else if (min==max && max > init) {
                limits = AttLimits::upperLimited(max);
            } else if (min < init && max > init) {
                limits = AttLimits::limitless();
            } else {
                limits = AttLimits::limitless();
            }
            m_fitsuite->addFitParameter(translated, init, limits);
        }
    }

    return m_fitsuite;
}

ParameterizedItem *RunFitWidget::getTopItemFromSelection(SessionModel *model,
                                                               const QString &itemType,
                                                               const QString &selectionType)
{
    QString selectedSample = m_fitModel->itemForIndex(QModelIndex())
            ->getChildOfType(Constants::FitSelectionType)
            ->getRegisteredProperty(selectionType).toString();

    if (selectedSample.isEmpty())
        return NULL;

    ParameterizedItem *top = 0;

    for (int i_row = 0; i_row < model->rowCount(QModelIndex()); ++i_row) {
        QModelIndex itemIndex = model->index(i_row, 0, QModelIndex());
        if (ParameterizedItem *item = model->itemForIndex(itemIndex)) {
            if (item->modelType()  == itemType) {
                if (item->displayName() == selectedSample)
                    top = item;
            }
        }
    }

    return top;
}
