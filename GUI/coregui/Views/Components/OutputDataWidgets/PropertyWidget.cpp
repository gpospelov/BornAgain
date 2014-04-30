#include "PropertyWidget.h"
#include "JobQueueModel.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"


PropertyWidget::PropertyWidget(QWidget *parent)
    : QWidget(parent)
    , m_variantManager(new QtVariantPropertyManager(this))
    , m_propertyBrowser(new QtTreePropertyBrowser(this))
    , m_centralPlot(0)
    , m_outputDataItem(0)
{
    maxWidth = 250;
    this->setMaximumWidth(maxWidth);


    /*QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();
    QtVariantProperty *priority = variantManager->addProperty(QVariant::Int, "Priority");

    priority->setToolTip("Task Priority");

    priority->setAttribute("minimum", 1);
    priority->setAttribute("maximum", 5);
    priority->setValue(3);

    QtVariantProperty *reportType = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), "Report Type");
    QStringList types;
    types << "Bug" << "Suggestion" << "To Do";
    reportType->setAttribute("enumNames", types);
    reportType->setValue(1); // current value will be "Suggestion"

    //QtVariantProperty *task1 = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), "Task 1");
    //task1->addSubProperty(priority);
    //task1->addSubProperty(reportType);

    QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(this);
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    browser->setFactoryForManager(variantManager, variantFactory);

    //browser->addProperty(task1);

    browser->addProperty(priority);
    browser->addProperty(reportType);*/

    m_variantManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    m_propertyBrowser->setFactoryForManager(m_variantManager, variantFactory);

}


void PropertyWidget::setupPropertyWidget(CentralPlot *centralPlot, OutputDataItem *outputDataItem)
{
    qDebug() << "PropertyWidget::setupPropertyWidget called";

    m_centralPlot = centralPlot;

    if(m_outputDataItem == outputDataItem) return;

    if(m_outputDataItem)
        disconnect(m_outputDataItem, SIGNAL(modified()), this, SLOT(onOutputDataItemModified()));

    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }

    propertyToId.clear();
    idToProperty.clear();

    m_outputDataItem = outputDataItem;
    connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(onOutputDataItemModified()));

    QtVariantProperty *property = m_variantManager->addProperty(QVariant::Bool, tr("Interpolation"));
    property->setToolTip("Interploation");
    property->setValue(outputDataItem->isInterpolated());
    addProperty(property, JobQueueXML::OutputDataInterpolatedAttribute);

    property = m_variantManager->addProperty(QVariant::Double, tr("zmin"));
    property->setValue(outputDataItem->getZaxisMin());
    property->setAttribute(QLatin1String("decimals"), 6);
    addProperty(property, JobQueueXML::OutputDataZminAttribute);

    property = m_variantManager->addProperty(QVariant::Double, tr("zmax"));
    property->setValue(outputDataItem->getZaxisMax());
    property->setAttribute(QLatin1String("decimals"), 6);
    addProperty(property, JobQueueXML::OutputDataZmaxAttribute);

}

int PropertyWidget::getWidth()
{
    return maxWidth;
}

void PropertyWidget::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    m_propertyBrowser->addProperty(property);
}


void PropertyWidget::valueChanged(QtProperty *property, const QVariant &value)
{
    QString id = propertyToId[property];

    qDebug() << "PropertyWidget::valueChanged: "<<id;

    //disconnect(m_outputDataItem, SIGNAL(modified()), this, SLOT(onOutputDataItemModified()));

    if (id == JobQueueXML::OutputDataInterpolatedAttribute) {

 
//        m_centralPlot->setInterpolate(value.toBool());
        m_outputDataItem->setInterpolated(value.toBool());

    } else if(id == JobQueueXML::OutputDataZminAttribute) {
        m_outputDataItem->setZaxisMin(value.toDouble());

    } else if(id == JobQueueXML::OutputDataZmaxAttribute) {
        m_outputDataItem->setZaxisMax(value.toDouble());


    }
    //connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(onOutputDataItemModified()));

}


void PropertyWidget::onOutputDataItemModified()
{
    qDebug() << "PropertyWidget::onOutputDataItemModified()";
    OutputDataItem *item = qobject_cast<OutputDataItem *>(sender());
    Q_ASSERT(item == m_outputDataItem);

    idToProperty[JobQueueXML::OutputDataInterpolatedAttribute]->setValue(m_outputDataItem->isInterpolated());
    idToProperty[JobQueueXML::OutputDataZminAttribute]->setValue(m_outputDataItem->getZaxisMin());
    idToProperty[JobQueueXML::OutputDataZmaxAttribute]->setValue(m_outputDataItem->getZaxisMax());

}

