#include "PropertyWidget.h"
#include "JobQueueModel.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"


PropertyWidget::PropertyWidget(QWidget *parent)
    : QWidget(parent)
    , m_variantManager(new QtVariantPropertyManager(this))
    , m_propertyBrowser(new QtTreePropertyBrowser(this))
    , m_outputDataItem(0)
{
    maxWidth = 250;
    this->setMaximumWidth(maxWidth);
    isProjection = true;
    initGradientVector();

    m_variantManager = new QtVariantPropertyManager(this);
    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    m_propertyBrowser->setFactoryForManager(m_variantManager, variantFactory);

}

void PropertyWidget::initGradientVector()
{
    m_gradientVector.append(QCPColorGradient::gpGrayscale);
    m_gradientVector.append(QCPColorGradient::gpHot);
    m_gradientVector.append(QCPColorGradient::gpCold);
    m_gradientVector.append(QCPColorGradient::gpNight);
    m_gradientVector.append(QCPColorGradient::gpCandy);
    m_gradientVector.append(QCPColorGradient::gpGeography);
    m_gradientVector.append(QCPColorGradient::gpIon);
    m_gradientVector.append(QCPColorGradient::gpThermal);
    m_gradientVector.append(QCPColorGradient::gpPolar);
    m_gradientVector.append(QCPColorGradient::gpSpectrum);
    m_gradientVector.append(QCPColorGradient::gpJet);
    m_gradientVector.append(QCPColorGradient::gpHues);
}


void PropertyWidget::setupPropertyWidget(OutputDataItem *outputDataItem, QCPColorGradient gradient)
{
    qDebug() << "PropertyWidget::setupPropertyWidget called";

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

    property = m_variantManager->addProperty(QVariant::Bool, tr("Logz"));
    property->setToolTip("Logz");
    property->setValue(outputDataItem->isLogz());
    addProperty(property, JobQueueXML::OutputDataLogzAttribute);

    property = m_variantManager->addProperty(QVariant::Double, tr("zmin"));
    property->setValue(outputDataItem->getZaxisMin());
    property->setAttribute(QLatin1String("decimals"), 6);
    addProperty(property, JobQueueXML::OutputDataZminAttribute);

    property = m_variantManager->addProperty(QVariant::Double, tr("zmax"));
    property->setValue(outputDataItem->getZaxisMax());
    property->setAttribute(QLatin1String("decimals"), 6);
    addProperty(property, JobQueueXML::OutputDataZmaxAttribute);

    property = m_variantManager->addProperty(QVariant::Bool, tr("Projections"));
    property->setToolTip("Projections");
    property->setValue(isProjection);
    addProperty(property, tr("Projections"));


    int gradIndex = 0;
    if(m_gradientVector.contains(gradient))
    {
        gradIndex = m_gradientVector.indexOf(gradient);
    }

    property = m_variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Gradient"));
    property->setToolTip("Gradient");
    QStringList types;
    types << "Grayscale" << "Hot" << "Cold" << "Night" << "Candy" << "Geography" << "Ion" << "Thermal" << "Polar" << "Spectrum" << "Jet" << "Hues";
    property->setAttribute("enumNames", types);
    property->setValue(gradIndex);
    addProperty(property, tr("Gradient"));

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

        m_outputDataItem->setInterpolated(value.toBool());

    } else if(id == JobQueueXML::OutputDataZminAttribute) {

        m_outputDataItem->setZaxisMin(value.toDouble());

    } else if(id == JobQueueXML::OutputDataZmaxAttribute) {

        m_outputDataItem->setZaxisMax(value.toDouble());

    } else if (id == JobQueueXML::OutputDataLogzAttribute) {

        m_outputDataItem->setLogz(value.toBool());

    } else if(id == tr("Projections")) {

        emit projectionsChanged(value.toBool());

    } else if(id == tr("Gradient")) {

        emit gradientChanged(m_gradientVector.at(value.toInt()));

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

