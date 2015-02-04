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
#include "UniversalPropertyEditor.h"
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
    , m_currentItem(0)
    , m_tabWidget(new QTabWidget)
    , m_propertyEditor(0)
    , m_commentsEditor(0)
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");

//    m_variantManager = new QtVariantPropertyManager(this);
//    m_readonlyManager = new QtVariantPropertyManager(this);
//    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
//                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

//    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
//    m_propertyBrowser->setFactoryForManager(m_variantManager, variantFactory);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);


    m_propertyEditor = new UniversalPropertyEditor(0, this);

    m_commentsEditor = new QTextEdit();

    QWidget *commentsWidget = new QWidget();
    QVBoxLayout * vlayout = new QVBoxLayout;
    vlayout->setMargin(8);
    vlayout->addWidget(m_commentsEditor);
    commentsWidget->setLayout(vlayout);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_propertyEditor, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, commentsWidget, "Details");

    mainLayout->addWidget(m_tabWidget);

    setLayout(mainLayout);

}


void JobPropertiesWidget::setModel(NJobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        if(m_jobModel)
            disconnect(m_jobModel,
                SIGNAL( selectionChanged(NJobItem *) ),
                this,
                SLOT( setItem(NJobItem *) )
                );

        m_jobModel = model;
        connect(m_jobModel,
            SIGNAL( selectionChanged(NJobItem *) ),
            this,
            SLOT( setItem(NJobItem *) )
            );

//        connect(m_jobModel, SIGNAL(dataChanged(QModelIndex, QModelIndex))
//                , this, SLOT(dataChanged(QModelIndex, QModelIndex)));
    }


}


//void JobPropertiesWidget::updateExpandState()
//{
//    QList<QtBrowserItem *> list = m_propertyBrowser->topLevelItems();
//    QListIterator<QtBrowserItem *> it(list);
//    while (it.hasNext()) {
//        QtBrowserItem *item = it.next();
//        QtProperty *prop = item->property();
//        idToExpanded[propertyToId[prop]] = m_propertyBrowser->isExpanded(item);
//    }
//}


void JobPropertiesWidget::setItem(NJobItem *jobItem)
{
    qDebug() << "JobPropertiesWidget::itemClicked" << jobItem->itemName();

    m_propertyEditor->setItem(jobItem);
//    Q_ASSERT(0);

//    if (m_currentItem == jobItem) return;

//    if (m_currentItem) {
//        clearEditor();

//        disconnect(m_currentItem, SIGNAL(propertyItemChanged(QString)),
//                this, SLOT(updateSubItems(QString)));
//    }

//    m_currentItem = jobItem;

//    if (!m_currentItem) return;

//    addItemProperties(m_currentItem);
//    connect(m_currentItem, SIGNAL(propertyItemChanged(QString)),
//            this, SLOT(updateSubItems(QString)));
//    connect(m_currentItem, SIGNAL(propertyChanged(QString)),
//            this, SLOT(onPropertyChanged(QString)));

}


//void JobPropertiesWidget::addItemProperties(const ParameterizedItem *item)
//{
//    QString item_type = item->modelType();
//    QtProperty *item_property = m_manager->addProperty(
//                QtVariantPropertyManager::groupTypeId(), item_type);

//    addSubProperties(item_property, item);
//    m_browser->addProperty(item_property);
//}


//void JobPropertiesWidget::addSubProperties(QtProperty *item_property,
//                                            const ParameterizedItem *item)
//{
//    QList<QByteArray> property_names = item->dynamicPropertyNames();
//    for (int i = 0; i < property_names.length(); ++i) {
//        QString prop_name = QString(property_names[i]);
//        PropertyAttribute prop_attribute = item->getPropertyAttribute(prop_name);

//        if(prop_attribute.getAppearance() & PropertyAttribute::HIDDEN) continue;

//        QVariant prop_value = item->property(prop_name.toUtf8().data());
//        int type = GUIHelpers::getVariantType(prop_value);

//        QtVariantProperty *subProperty = 0;
//        if (m_manager->isPropertyTypeSupported(type)) {

//            if(prop_attribute.getLabel().isEmpty()) {
//                subProperty = m_manager->addProperty(type, prop_name);
//            } else {
//                subProperty = m_manager->addProperty(type, prop_attribute.getLabel());
//            }

//            subProperty->setValue(prop_value);

//            if(type == QVariant::Double) {
//                subProperty->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
//                 AttLimits limits = prop_attribute.getLimits();
//                 if(limits.hasLowerLimit()) subProperty->setAttribute(QLatin1String("minimum"), limits.getLowerLimit());
//                 if(limits.hasUpperLimit()) subProperty->setAttribute(QLatin1String("maximum"), limits.getUpperLimit());
//            }

//            QString toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), prop_name);
//            if(!toolTip.isEmpty()) subProperty->setToolTip(toolTip);

//            if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) {
//                subProperty->setEnabled(false);
//            }

//            if (item->getSubItems().contains(prop_name)) {
//                ParameterizedItem *subitem = item->getSubItems()[prop_name];
//                if (subitem) {
//                    addSubProperties(subProperty, subitem);
//                }
//            }

//        } else {
//            subProperty = m_read_only_manager->addProperty(QVariant::String,
//                                                         prop_name);
//            subProperty->setValue(QLatin1String("< Unknown Type >"));
//            subProperty->setEnabled(false);
//        }

//        item_property->addSubProperty(subProperty);
//        ParameterizedItem *non_const_item =
//                const_cast<ParameterizedItem *>(item);
//        ItemIndexPair item_index_pair(non_const_item, i);
//        m_property_to_item_index_pair[subProperty] = item_index_pair;
//        m_item_to_index_to_property[item][i] = subProperty;
//        m_item_to_propertyname_to_qtvariantproperty[item][prop_name] = subProperty;
//    }
//}


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

//}


//void JobPropertiesWidget::addProperty(QtVariantProperty *property, const QString &id)
//{
//    propertyToId[property] = id;
//    idToProperty[id] = property;
//    QtBrowserItem *item = m_propertyBrowser->addProperty(property);
//    if (idToExpanded.contains(id))
//        m_propertyBrowser->setExpanded(item, idToExpanded[id]);
//}


//void JobPropertiesWidget::valueChanged(QtProperty *property, const QVariant &value)
//{
//    Q_ASSERT(0);
//    Q_UNUSED(property);
//    Q_UNUSED(value);
////    if (!propertyToId.contains(property))
////        return;

////    if (!m_currentItem)
////        return;

////    QString id = propertyToId[property];
////    if (id == JobQueueXML::JobNameAttribute) {
////        m_currentItem->setName(value.value<QString>());
////    }
//}


////! to update properties of currently selected item if they were changed from outside
//void JobPropertiesWidget::dataChanged(const QModelIndex &index, const QModelIndex &)
//{
//    qDebug() << "JobPropertiesWidget::dataChanged(const QModelIndex &index, const QModelIndex &)";
////    Q_UNUSED(index);
//    NJobItem *jobItem = m_jobModel->getJobItemForIndex(index);
//    if(jobItem == m_currentItem) {
//          Q_ASSERT(0);
////        idToProperty[JobQueueXML::JobNameAttribute]->setValue(jobItem->getName());
////        idToProperty[JobQueueXML::JobStatusAttribute]->setValue(jobItem->getStatusString());
////        idToProperty[JobQueueXML::JobBeginTimeAttribute]->setValue(jobItem->getBeginTime());
////        idToProperty[JobQueueXML::JobEndTimeAttribute]->setValue(jobItem->getEndTime());
//    }
//}
