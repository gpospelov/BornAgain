#include "PropertyWidget.h"
#include "JobQueueModel.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"


PropertyWidget::PropertyWidget(QWidget *parent)
    : QWidget(parent)
    , m_variantManager(new QtVariantPropertyManager(this))
    , m_propertyBrowser(new QtTreePropertyBrowser(this))
{
    this->setMaximumWidth(250);



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
}

void PropertyWidget::setupPropertyWidget(CentralPlot *centralPlot, OutputDataItem *outputDataItem)
{
    qDebug() << "PropertyWidget::setupPropertyWidget called";

    //if(m_current_item == outputdata) return;

    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }

    propertyToId.clear();
    idToProperty.clear();

    m_outputDataItem = outputDataItem;
    m_centralPlot = centralPlot;

    m_variantManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *m_variantFactory = new QtVariantEditorFactory(this);
    m_propertyBrowser->setFactoryForManager(m_variantManager, m_variantFactory);


    QtVariantProperty *property = m_variantManager->addProperty(QVariant::Bool, tr("Interpolation"));
    property->setToolTip("Interploation");
    property->setValue(outputDataItem->isInterpolated());
    addProperty(property, JobQueueXML::OutputDataInterpolatedAttribute);

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

    qDebug() << "ID: "<<id;

    if (id == JobQueueXML::OutputDataInterpolatedAttribute) {
        m_centralPlot->setInterpolate(value.toBool());

        //m_outputDataItem->setInterpolated(value.toBool());

    }
}
