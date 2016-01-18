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
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

RunFitWidget::RunFitWidget(QWidget *parent) : QWidget(parent)
  , m_start_button(0)
  , m_stop_button(0)
  , m_interval_label(0)
  , m_interval_slider(0)
  , m_runfitmanager(new RunFitManager(this))
  , m_fitprogress(new FitProgressWidget())
{
    m_guifitobserver = boost::shared_ptr<GUIFitObserver>(new GUIFitObserver(this));

    m_start_button  = new QPushButton();
    m_start_button->setText(tr("Start"));
    m_stop_button = new QPushButton();
    m_stop_button->setText(tr("Stop"));
    m_stop_button->setEnabled(false);
    m_interval_label = new QLabel();
    m_interval_slider = new QSlider();
    m_interval_slider->setOrientation(Qt::Horizontal);
    m_interval_slider->setRange(1,20);
    m_interval_slider->setValue(10);
    m_interval_slider->setMaximumWidth(150);
    m_interval_slider->setMinimumWidth(150);
    onIntervalChanged(10);
    m_guifitobserver->setInterval(10);

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
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_interval_slider, SIGNAL(sliderMoved(int)), this, SLOT(onIntervalChanged(int)));
    connect(m_start_button, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(m_stop_button, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(m_runfitmanager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_runfitmanager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));
    connect(m_interval_slider, SIGNAL(sliderMoved(int)),
                m_guifitobserver.get(), SLOT(setInterval(int)));
    connect(m_guifitobserver.get(), SIGNAL(updateStatus(const QString&)),
                m_fitprogress, SLOT(updateStatus(const QString&)));

    // used for test purposes
    boost::shared_ptr<FitSuite> suite = init_test_fitsuite();
    suite->attachObserver(m_guifitobserver);
    m_runfitmanager->setFitSuite(suite);



}

void RunFitWidget::onIntervalChanged(int value)
{
    m_interval_label->setText(QString("Update every %1th iteration").arg(value));
}

void RunFitWidget::onStartClicked()
{
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
    SampleBuilderFactory builderFactory;
    boost::scoped_ptr<ISample> sample(builderFactory.createSample("CylindersInBABuilder"));

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    simulation->setDetectorParameters(100,-2*Units::degree, 2*Units::degree,100,0,2*Units::degree);
    simulation->setSample(*sample.get());
    simulation->runSimulation();

    boost::scoped_ptr<OutputData<double> > real_data(simulation->getDetectorIntensity());

    boost::shared_ptr<FitSuite> m_fitsuite = boost::shared_ptr<FitSuite>(new FitSuite());
    if (true)
    {
    m_fitsuite->setMinimizer("Genetic");
    m_fitsuite->getMinimizer()->getOptions()->setValue("RandomSeed",1);

    m_fitsuite->addFitParameter("*Height", 4.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);
    m_fitsuite->addFitParameter("*Radius", 5.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);
    }
    else
    {

        m_fitsuite->addFitParameter("*Height", 3.5 * Units::nanometer, AttLimits::lowerLimited(0.01));
        m_fitsuite->addFitParameter("*Radius", 4.5 * Units::nanometer, AttLimits::lowerLimited(0.01));
    }

    m_fitsuite->addSimulationAndRealData(*simulation.get(), *real_data.get());
    return m_fitsuite;
}
