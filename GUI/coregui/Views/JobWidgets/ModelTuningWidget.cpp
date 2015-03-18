// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningWidget.cpp
//! @brief     Implements class ModelTuningWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelTuningWidget.h"
#include "JobItem.h"
#include "SliderSettingsWidget.h"
#include "ParameterModelBuilder.h"
#include "GUIHelpers.h"
#include "ModelTuningDelegate.h"
#include "JobQueueData.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include <QToolButton>
#include <QCommandLinkButton>
#include <QDebug>
#include <QMessageBox>


ModelTuningWidget::ModelTuningWidget(JobQueueData *jobQueueData, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueData(jobQueueData)
    , m_currentJobItem(0)
    , m_sliderSettingsWidget(0)
    , m_parameterModel(0)
    , m_delegate(new ModelTuningDelegate)
    , m_sampleModelBackup(0)
    , m_instrumentModelBackup(0)
    , m_infoPanel(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_sliderSettingsWidget = new SliderSettingsWidget();
    connect(m_sliderSettingsWidget, SIGNAL(sliderRangeFactorChanged(double)), this, SLOT(onSliderValueChanged(double)));
    connect(m_sliderSettingsWidget, SIGNAL(lockzChanged(bool)), this, SLOT(onLockZValueChanged(bool)));

    m_treeView = new QTreeView();
    m_treeView->setStyleSheet(
        "QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item "
        "{border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:"
        "adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:"
        "!has-children:!has-siblings:adjoins-item {border-image: "
        "url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed"
        ",QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: "
        "url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,"
        "QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: "
        "url(:/images/treeview-branch-open.png);}");

    m_treeView->setItemDelegate(m_delegate);
    connect(m_delegate, SIGNAL(currentLinkChanged(ItemLink)), this, SLOT(onCurrentLinkChanged(ItemLink)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // setting up bottom info panel
    m_infoPanel = new QWidget;
    m_infoPanel->setStyleSheet("background-color:white;");
    QHBoxLayout *infoPanelLayout = new QHBoxLayout;
    infoPanelLayout->setContentsMargins(0, 0, 0, 0);

    m_infoLinkButton = new QCommandLinkButton;
    m_infoLinkButton->setText("Houston, we have a problem ...");
    infoPanelLayout->addWidget(m_infoLinkButton);
    m_infoPanel->setLayout(infoPanelLayout);
    m_infoPanel->hide();
    connect(m_infoLinkButton, SIGNAL(clicked()), this, SLOT(onInfoLinkButtonClicked()));

    // assembling all together
    mainLayout->addWidget(m_sliderSettingsWidget);
    mainLayout->addWidget(m_treeView);
    mainLayout->addWidget(m_infoPanel);

    setLayout(mainLayout);
}

ModelTuningWidget::~ModelTuningWidget()
{
    delete m_parameterModel;
    delete m_sampleModelBackup;
    delete m_instrumentModelBackup;
}

void ModelTuningWidget::setCurrentItem(JobItem *item)
{
    qDebug() << "ModelTuningWidget::setCurrentItem" << item;
//    if(m_currentJobItem != item) {
//        m_currentJobItem = item;
//        updateParameterModel();
//        backupModels();
//    }

    if (m_currentJobItem == item) return;

    if (m_currentJobItem) {
        disconnect(m_currentJobItem, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_currentJobItem = item;

    if (!m_currentJobItem) return;

    updateParameterModel();
    backupModels();

    //updateItem(m_currentJobItem);

    connect(m_currentJobItem, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

void ModelTuningWidget::onCurrentLinkChanged(ItemLink link)
{
    qDebug() << "ModelTuningWidget::onCurrentLinkChanged";
    Q_ASSERT(m_currentJobItem);

    if(m_currentJobItem->isRunning())
        return;

    if(link.getItem()) {
        qDebug() << "ModelTuningWidget::onCurrentLinkChanged() -> Starting to tune model" << link.getItem()->modelType() << link.getPropertyName() ;
        link.updateItem();
        m_jobQueueData->runJob(m_currentJobItem->getIdentifier());
    }
}


void ModelTuningWidget::onSliderValueChanged(double value)
{
    m_delegate->setSliderRangeFactor(value);
}

void ModelTuningWidget::onLockZValueChanged(bool value)
{
    if(!m_currentJobItem) return;
    if(IntensityDataItem *intensityDataItem = m_currentJobItem->getIntensityDataItem()) {
        qDebug() << "ModelTuningWidget::onLockZValueChanged(bool value) ->" << value;
        intensityDataItem->setZAxisLocked(value);
    }
}


void ModelTuningWidget::updateParameterModel()
{
    qDebug() << "ModelTuningWidget::updateParameterModel()";
    if(m_parameterModel) {
        m_treeView->setModel(0);
        delete m_parameterModel;
        m_parameterModel = 0;
    }

    if(!m_currentJobItem) return;

    if(!m_currentJobItem->getSampleModel() || !m_currentJobItem->getInstrumentModel())
        throw GUIHelpers::Error("ModelTuningWidget::updateParameterModel() -> Error."
                                "JobItem doesn't have sample or instrument model.");

    m_parameterModel = ParameterModelBuilder::createParameterModel(
                m_currentJobItem->getSampleModel(), m_currentJobItem->getInstrumentModel());
    m_treeView->setModel(m_parameterModel);
    m_treeView->setColumnWidth(0, 170);
    m_treeView->expandAll();
}


//! Creates backup copies of JobItem's sample and instrument models
void ModelTuningWidget::backupModels()
{
    qDebug() << "ModelTuningWidget::backupModels()";
    if(!m_currentJobItem) return;

    if(!m_sampleModelBackup)
        m_sampleModelBackup = m_currentJobItem->getSampleModel()->createCopy();

    if(!m_instrumentModelBackup)
        m_instrumentModelBackup = m_currentJobItem->getInstrumentModel()->createCopy();
}

void ModelTuningWidget::restoreModelsOfCurrentJobItem()
{
    if(m_currentJobItem->isRunning())
        return;

//    qDebug() << "ModelTuningWidget::restoreModelsOfCurrentJobItem()";
    Q_ASSERT(m_sampleModelBackup);
    Q_ASSERT(m_instrumentModelBackup);
    Q_ASSERT(m_currentJobItem);

//    qDebug() << "ModelTuningWidget::restoreModelsOfCurrentJobItem() current"
//             << m_currentJobItem->getSampleModel() << m_currentJobItem->getInstrumentModel()
//             << " backup" << m_sampleModelBackup << m_instrumentModelBackup;

    m_currentJobItem->setSampleModel(m_sampleModelBackup->createCopy());
    m_currentJobItem->setInstrumentModel(m_instrumentModelBackup->createCopy());
    updateParameterModel();

    m_jobQueueData->runJob(m_currentJobItem->getIdentifier());
}

void ModelTuningWidget::onInfoLinkButtonClicked()
{
    if(m_currentJobItem && !m_currentJobItem->getComments().isEmpty()) {
        QString message;
        message.append("Current parameter values cause simulation failure.\n\n");
        message.append(m_currentJobItem->getComments());

        QMessageBox::warning(this, tr("Simulation failed"), message);
    }
}

void ModelTuningWidget::onPropertyChanged(const QString &property_name)
{
    if(property_name == JobItem::P_STATUS) {
        if(m_currentJobItem->isFailed()) {
            m_infoPanel->show();
        } else {
            m_infoPanel->hide();
        }
    }
}


