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
    maxWidth = 230;
    this->setMaximumWidth(maxWidth);
    this->setMinimumHeight(800);

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

    m_projectionsProperty = m_variantManager->addProperty(QVariant::Bool, tr("Projections"));
    m_projectionsProperty->setToolTip("Projections");
    m_projectionsProperty->setValue(isProjection);
    addProperty(m_projectionsProperty, tr("Projections"));

    m_interpolationProperty = m_variantManager->addProperty(QVariant::Bool, tr("Interpolation"));
    m_interpolationProperty->setToolTip("Interploation");
    m_interpolationProperty->setValue(outputDataItem->isInterpolated());
    addProperty(m_interpolationProperty, JobQueueXML::OutputDataInterpolatedAttribute);

    m_logzProperty = m_variantManager->addProperty(QVariant::Bool, tr("Logz"));
    m_logzProperty->setToolTip("Logz");
    m_logzProperty->setValue(outputDataItem->isLogz());
    addProperty(m_logzProperty, JobQueueXML::OutputDataLogzAttribute);

    m_zminProperty = m_variantManager->addProperty(QVariant::Double, tr("zmin"));
    m_zminProperty->setValue(outputDataItem->getZaxisMin());
    m_zminProperty->setAttribute(QLatin1String("decimals"), 6);
    addProperty(m_zminProperty, JobQueueXML::OutputDataZminAttribute);

    m_zmaxProperty = m_variantManager->addProperty(QVariant::Double, tr("zmax"));
    m_zmaxProperty->setValue(outputDataItem->getZaxisMax());
    m_zmaxProperty->setAttribute(QLatin1String("decimals"), 6);
    addProperty(m_zmaxProperty, JobQueueXML::OutputDataZmaxAttribute);

    qDebug() << "zxmin zxmax" << outputDataItem->getZaxisMin() << outputDataItem->getZaxisMax();



    int gradIndex = 0;
    if(m_gradientVector.contains(gradient))
    {
        gradIndex = m_gradientVector.indexOf(gradient);
    }

    m_gradientProperty = m_variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Gradient"));
    m_gradientProperty->setToolTip("Gradient");
    QStringList types;
    types << "Grayscale" << "Hot" << "Cold" << "Night" << "Candy" << "Geography" << "Ion" << "Thermal" << "Polar" << "Spectrum" << "Jet" << "Hues";
    m_gradientProperty->setAttribute("enumNames", types);
    m_gradientProperty->setValue(gradIndex);
    addProperty(m_gradientProperty, tr("Gradient"));

    m_xtitleProperty = m_variantManager->addProperty(QVariant::String, tr("x-title"));
    m_xtitleProperty->setValue(outputDataItem->getXaxisTitle());
    addProperty(m_xtitleProperty, JobQueueXML::OutputDataXtitleAttribute);

    m_ytitleProperty = m_variantManager->addProperty(QVariant::String, tr("y-title"));
    m_ytitleProperty->setValue(outputDataItem->getYaxisTitle());
    addProperty(m_ytitleProperty, JobQueueXML::OutputDataYtitleAttribute);

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
        isProjection = value.toBool();
        emit projectionsChanged(value.toBool());

    } else if(id == tr("Gradient")) {

        emit gradientChanged(m_gradientVector.at(value.toInt()));

    } else if(id == JobQueueXML::OutputDataXtitleAttribute) {

        m_outputDataItem->setXaxisTitle(value.toString());

    } else if(id == JobQueueXML::OutputDataYtitleAttribute) {

        m_outputDataItem->setYaxisTitle(value.toString());

    }
    //connect(m_outputDataItem, SIGNAL(modified()), this, SLOT(onOutputDataItemModified()));

}


void PropertyWidget::onOutputDataItemModified()
{
    qDebug() << "PropertyWidget::onOutputDataItemModified()";
    OutputDataItem *item = qobject_cast<OutputDataItem *>(sender());
    (void)item;
    Q_ASSERT(item == m_outputDataItem);

    idToProperty[JobQueueXML::OutputDataInterpolatedAttribute]->setValue(m_outputDataItem->isInterpolated());
    idToProperty[JobQueueXML::OutputDataZminAttribute]->setValue(m_outputDataItem->getZaxisMin());
    idToProperty[JobQueueXML::OutputDataZmaxAttribute]->setValue(m_outputDataItem->getZaxisMax());
    idToProperty[JobQueueXML::OutputDataXtitleAttribute]->setValue(m_outputDataItem->getXaxisTitle());
    idToProperty[JobQueueXML::OutputDataYtitleAttribute]->setValue(m_outputDataItem->getYaxisTitle());
    idToProperty[JobQueueXML::OutputDataLogzAttribute]->setValue(m_outputDataItem->isLogz());

}

void PropertyWidget::toggleProjections()
{
  m_projectionsProperty->setValue(!isProjection);
}

