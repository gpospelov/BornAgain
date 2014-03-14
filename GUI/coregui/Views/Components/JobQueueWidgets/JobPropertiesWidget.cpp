#include "JobPropertiesWidget.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include <QVBoxLayout>
#include <QDebug>

JobPropertiesWidget::JobPropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_variantManager(new QtVariantPropertyManager(this))
    , m_propertyBrowser(new QtTreePropertyBrowser(this))
    , m_currentItem(0)
{
//    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");

    m_variantManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    m_propertyBrowser->setFactoryForManager(m_variantManager, variantFactory);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_propertyBrowser);
    setLayout(mainLayout);

}


void JobPropertiesWidget::setModel(JobQueueModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobQueueModel) {
        m_jobQueueModel = model;
//        connect(m_jobQueueModel,
//            SIGNAL( selectionChanged(JobQueueItem *) ),
//            this,
//            SLOT( itemClicked(JobQueueItem *) )
//            );
        connect(m_jobQueueModel,
            SIGNAL( selectionChanged(JobQueueItem *) ),
            this,
            SLOT( itemClicked(JobQueueItem *) )
            );
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


void JobPropertiesWidget::itemClicked(JobQueueItem *jobItem)
{
    qDebug() << "JobPropertiesWidget::itemClicked" << jobItem->getName();

    updateExpandState();

    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }
    propertyToId.clear();
    idToProperty.clear();

    m_currentItem = jobItem;
//    if (!currentItem) {
//        deleteAction->setEnabled(false);
//        return;
//    }

//    deleteAction->setEnabled(true);

    QtVariantProperty *property;

    property = m_variantManager->addProperty(QVariant::String, tr("Name"));
    property->setValue(jobItem->getName());
    addProperty(property, JobQueueXML::JobNameAttribute);

    property = m_variantManager->addProperty(QVariant::String, tr("Status"));
    property->setValue(jobItem->getStatus());
    addProperty(property, JobQueueXML::JobStatusAttribute);

    property = m_variantManager->addProperty(QVariant::String, tr("Begin Time"));
    property->setValue(jobItem->getBeginTime());
    addProperty(property, JobQueueXML::JobBeginTimeAttribute);

    property = m_variantManager->addProperty(QVariant::String, tr("End Time"));
    property->setValue(jobItem->getEndTime());
    addProperty(property, JobQueueXML::JobEndTimeAttribute);

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
    qDebug() << "JobPropertiesWidget::valueChanged()";

    if (!propertyToId.contains(property))
        return;

    if (!m_currentItem)
        return;

    QString id = propertyToId[property];
    if (id == JobQueueXML::JobNameAttribute) {
        m_currentItem->setName(value.value<QString>());
    }

    m_jobQueueModel->jobQueueItemIsChanged(m_currentItem);

}

