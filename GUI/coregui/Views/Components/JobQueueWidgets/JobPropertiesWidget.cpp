// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobPropertiesWidget.cpp
//! @brief     Implements class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobPropertiesWidget.h"
//#include "JobQueueModel.h"
//#include "JobItem.h"
#include "NJobModel.h"
#include "NJobItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include <QVBoxLayout>
#include <QTabBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QDebug>

JobPropertiesWidget::JobPropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_variantManager(new QtVariantPropertyManager(this))
    , m_propertyBrowser(new QtTreePropertyBrowser(this))
    , m_currentItem(0)
    , m_tabWidget(new QTabWidget)
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");

    m_variantManager = new QtVariantPropertyManager(this);
    m_readonlyManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    m_propertyBrowser->setFactoryForManager(m_variantManager, variantFactory);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_commentsEditor = new QTextEdit();

    QWidget *commentsWidget = new QWidget();
    QVBoxLayout * vlayout = new QVBoxLayout;
    vlayout->setMargin(8);
    vlayout->addWidget(m_commentsEditor);
    commentsWidget->setLayout(vlayout);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_propertyBrowser, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, commentsWidget, "Details");

    mainLayout->addWidget(m_tabWidget);

    setLayout(mainLayout);

}


void JobPropertiesWidget::setModel(NJobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        m_jobModel = model;
        connect(m_jobModel,
            SIGNAL( selectionChanged(NJobItem *) ),
            this,
            SLOT( itemClicked(NJobItem *) )
            );

        connect(m_jobModel, SIGNAL(dataChanged(QModelIndex, QModelIndex))
                , this, SLOT(dataChanged(QModelIndex, QModelIndex)));
    }
}


void JobPropertiesWidget::updateExpandState()
{
    QList<QtBrowserItem *> list = m_propertyBrowser->topLevelItems();
    QListIterator<QtBrowserItem *> it(list);
    while (it.hasNext()) {
        QtBrowserItem *item = it.next();
        QtProperty *prop = item->property();
        idToExpanded[propertyToId[prop]] = m_propertyBrowser->isExpanded(item);
    }
}


void JobPropertiesWidget::itemClicked(NJobItem *jobItem)
{
    qDebug() << "JobPropertiesWidget::itemClicked" << jobItem->itemName();
    Q_ASSERT(0);

//    updateExpandState();

//    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
//    while (itProp != propertyToId.constEnd()) {
//        delete itProp.key();
//        itProp++;
//    }
//    propertyToId.clear();
//    idToProperty.clear();

//    m_currentItem = jobItem;
////    if (!currentItem) {
////        deleteAction->setEnabled(false);
////        return;
////    }

////    deleteAction->setEnabled(true);

//    QtVariantProperty *property;

//    property = m_variantManager->addProperty(QVariant::String, tr("Name"));
//    property->setValue(jobItem->getName());
//    addProperty(property, JobQueueXML::JobNameAttribute);

//    property = m_readonlyManager->addProperty(QVariant::String, tr("Sample"));
//    if(jobItem->getSampleModel()) property->setValue(jobItem->getSampleModel()->getSampleMap().firstKey());
//    addProperty(property, "Sample");

//    property = m_readonlyManager->addProperty(QVariant::String, tr("Instrument"));
//    if(jobItem->getInstrumentModel()) property->setValue(jobItem->getInstrumentModel()->getInstrumentMap().firstKey());
//    addProperty(property, "Instrument");

//    property = m_readonlyManager->addProperty(QVariant::String, tr("Status"));
//    property->setValue(jobItem->getStatusString());
//    addProperty(property, JobQueueXML::JobStatusAttribute);

//    property = m_readonlyManager->addProperty(QVariant::String, tr("Begin Time"));
//    property->setValue(jobItem->getBeginTime());
//    addProperty(property, JobQueueXML::JobBeginTimeAttribute);

//    property = m_readonlyManager->addProperty(QVariant::String, tr("End Time"));
//    property->setValue(jobItem->getEndTime());
//    addProperty(property, JobQueueXML::JobEndTimeAttribute);

//    if(jobItem->getStatus() == JobItem::FAILED) {
//        m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::red);
//    } else {
//        m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::black);
//    }
//    m_commentsEditor->setText(jobItem->getComments());

}


void JobPropertiesWidget::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = m_propertyBrowser->addProperty(property);
    if (idToExpanded.contains(id))
        m_propertyBrowser->setExpanded(item, idToExpanded[id]);
}


void JobPropertiesWidget::valueChanged(QtProperty *property, const QVariant &value)
{
    Q_ASSERT(0);
    Q_UNUSED(property);
    Q_UNUSED(value);
//    if (!propertyToId.contains(property))
//        return;

//    if (!m_currentItem)
//        return;

//    QString id = propertyToId[property];
//    if (id == JobQueueXML::JobNameAttribute) {
//        m_currentItem->setName(value.value<QString>());
//    }
}


//! to update properties of currently selected item if they were changed from outside
void JobPropertiesWidget::dataChanged(const QModelIndex &index, const QModelIndex &)
{
    qDebug() << "JobPropertiesWidget::dataChanged(const QModelIndex &index, const QModelIndex &)";
//    Q_UNUSED(index);
    NJobItem *jobItem = m_jobModel->getJobItemForIndex(index);
    if(jobItem == m_currentItem) {
          Q_ASSERT(0);
//        idToProperty[JobQueueXML::JobNameAttribute]->setValue(jobItem->getName());
//        idToProperty[JobQueueXML::JobStatusAttribute]->setValue(jobItem->getStatusString());
//        idToProperty[JobQueueXML::JobBeginTimeAttribute]->setValue(jobItem->getBeginTime());
//        idToProperty[JobQueueXML::JobEndTimeAttribute]->setValue(jobItem->getEndTime());
    }
}
