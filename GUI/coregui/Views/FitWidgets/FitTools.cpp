// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningWidget.cpp
//! @brief     Implements class ModelTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobItem.h"
#include "FilterPropertyProxy.h"
#include "JobModel.h"
#include "ModelPath.h"
#include "RunFitManager.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "FitSuite.h"
#include "Units.h"
#include "IntensityDataItem.h"
#include "DomainSimulationBuilder.h"
#include "GUIFitObserver.h"
#include "MultiLayerItem.h"
#include "ParameterTreeItems.h"
#include "SessionItem.h"
#include "ObsoleteRealDataWindow.h"

#include "FitTools.h"

#include <boost/scoped_ptr.hpp>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QDebug>
#include <QMessageBox>
#include <QSlider>
#include <string>
#include <QStack>


FitTools::FitTools(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(jobModel)
    , m_currentJobItem(0)
    , m_selectionModel(0)
    , m_startButton(new QPushButton)
    , m_stopButton(new QPushButton)
    , m_intervalSlider(new QSlider)
    , m_realData(new QPushButton)
    , m_manager(new RunFitManager(parent))
    , m_observer(0)
    , m_realDataWindow(new ObsoleteRealDataWindow(this))
{
    m_observer = std::shared_ptr<GUIFitObserver>(new GUIFitObserver());
    this->hide();
    QHBoxLayout *layout = new QHBoxLayout;
    m_startButton->setText("Fit selected Parameters");
    m_stopButton->setText("Stop");
    m_intervalSlider->setOrientation(Qt::Horizontal);
    m_intervalSlider->setRange(1,20);
    m_intervalSlider->setMaximumWidth(150);
    m_intervalSlider->setMinimumWidth(150);
    m_intervalSlider->setFocusPolicy(Qt::NoFocus);
    m_intervalSlider->setValue(10);
    m_realData->setText("Data");
    connect(m_startButton, SIGNAL(clicked(bool)), this, SLOT(onStartClick()));
    connect(m_stopButton, SIGNAL(clicked(bool)), this, SLOT(onStopClicked()));
    connect(m_manager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_manager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));
    connect(m_manager, SIGNAL(error(QString)), this, SLOT(onError(QString)));
    connect(m_observer.get(), SIGNAL(updatePlots(OutputData<double>*,OutputData<double>*)),
            this, SLOT(onUpdatePlots(OutputData<double>*,OutputData<double>*)));
    connect(m_observer.get(), SIGNAL(updateParameters(QStringList,QVector<double>)),
            this, SLOT(onUpdateParameters(QStringList,QVector<double>)));
    connect(m_intervalSlider, SIGNAL(valueChanged(int)), m_observer.get(), SLOT(setInterval(int)));
    connect(m_realData, SIGNAL(clicked(bool)), this, SLOT(onRealData()));
    m_observer->setInterval(10);
    layout->addWidget(m_startButton);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_intervalSlider);
    layout->addWidget(m_realData);
    this->setLayout(layout);
}

void FitTools::setCurrentItem(JobItem *item, QItemSelectionModel *selection)
{
    m_currentJobItem = item;
    m_selectionModel = selection;
    if (m_currentJobItem->getItemValue(JobItem::P_WITH_FITTING).toBool()) {
        this->show();
    } else {
        this->hide();
    }
    m_realDataWindow->setItem(dynamic_cast<IntensityDataItem*>(item->getItem(JobItem::T_REALDATA)));
}

void FitTools::onStartClick()
{
    if (!m_currentJobItem)
        return;

    try {
    DomainSimulationBuilder builder;
    const std::unique_ptr<GISASSimulation> simulation(
                builder.getSimulation(m_currentJobItem->getMultiLayerItem(),
                                        m_currentJobItem->getInstrumentItem()));

        std::shared_ptr<FitSuite> m_fitsuite = std::shared_ptr<FitSuite>(new FitSuite());

        //fitSuite->initPrint(100);
        //m_fitsuite->setMinimizer("Genetic");
        //m_fitsuite->getMinimizer()->getOptions()->setValue("RandomSeed",1);
        m_fitsuite->attachObserver(m_observer);

        QModelIndexList indexes = m_selectionModel->selectedIndexes();
        for (QModelIndex index : indexes) {
            QModelIndex sourceIndex = FilterPropertyProxy::toSourceIndex(index);
            if (sourceIndex.column() == 0) {
                SessionItem *item = m_jobModel->itemForIndex(sourceIndex);
                if (item && item->modelType() == Constants::ParameterType) {
                    QString path = ModelPath::getPathFromIndex(item->index());
                    qDebug() << "QQQ 1.1" << path;
                    int containerEnd = path.indexOf("Container/") + 10;
                    path = path.mid(containerEnd);
                    qDebug() << "QQQ 1.2" << path;
                    std::string outpath = "*" + ModelPath::translateParameterName(m_currentJobItem->getMultiLayerItem()->parent(), path);
                    qDebug() << "QQQ 1.3" << QString::fromStdString(outpath);

                    item->setItemValue(ParameterItem::P_DOMAIN, QString::fromStdString(outpath));
                    m_fitsuite->addFitParameter(outpath, item->value().toDouble(), dynamic_cast<ParameterItem*>(item)->getLinkedItem()->limits());
                }
            }
        }

        //m_fitsuite->addFitParameter("*Radius", 5.5 * Units::nanometer, AttLimits::limited(4.0, 6.0), 0.1);

        auto x = dynamic_cast<IntensityDataItem*>(m_currentJobItem->getItem(JobItem::T_REALDATA))->getOutputData();
        if (x)
            m_fitsuite->addSimulationAndRealData(*simulation.get(), *x);


    m_manager->setFitSuite(m_fitsuite);
    m_observer->finishedPlotting();
    m_manager->runFitting();
    } catch(std::exception& e) {
        QMessageBox box;
        box.setText(e.what());
        box.exec();
    }
}

void FitTools::onFittingStarted()
{
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
}

void FitTools::onFittingFinished()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
}

void FitTools::onStopClicked()
{
    m_manager->interruptFitting();
}

void FitTools::onError(const QString &text)
{
    QMessageBox box;
    box.setText(text);
    box.exec();
}

void FitTools::onUpdatePlots(OutputData<double> *sim, OutputData<double> *)
{
    // hack to preserve axis information
    auto data = m_currentJobItem->getIntensityDataItem()->getOutputData()->clone();
    data->setRawDataVector(sim->getRawDataVector());
    m_currentJobItem->getIntensityDataItem()->setOutputData(data);
    m_observer->finishedPlotting();
}

void FitTools::onUpdateParameters(const QStringList &parameters, QVector<double> values)
{
    // TODO update parameters
    SessionItem *current = m_currentJobItem->getItem(JobItem::T_PARAMETER_TREE); //this is container
    QStack<SessionItem*> stack;
    stack.push(current);
    while(!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == Constants::ParameterLabelType) {
            for (SessionItem *child : current->getItems()) {
                stack.push(child);
            }
        } else {
            QString domainPath = current->getItemValue(ParameterItem::P_DOMAIN).toString();
            if (parameters.contains(domainPath)) {
                int index = parameters.indexOf(domainPath);
                current->setValue(values[index]);
            }
        }
    }
}

void FitTools::onRealData()
{
    m_realDataWindow->show();
}
