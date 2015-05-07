#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include <iostream>

DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_mainLayout(new QHBoxLayout)
    , m_plotwidget(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    BeamWavelengthItem *item = new BeamWavelengthItem;

//    DistributionItem *item = new DistributionGaussianItem;
    m_plotwidget = new DistributionWidget;

    m_propertyEditor = new AwesomePropertyEditor(this);

// main layout
//    QVBoxLayout *mainLayout = new QVBoxLayout;


    setItem(item);
    m_mainLayout->addWidget(m_propertyEditor);
    m_mainLayout->addWidget(m_plotwidget, 1);
    setLayout(m_mainLayout);


}



void DistributionEditor::setItem(ParameterizedItem *item)
{
    m_propertyEditor->setItem(item);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));
    }
    m_item = item;

    if (!m_item) return;

//    plotItem(m_item);
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(onSubItemChanged(QString)));

}

//void DistributionEditor::plotItem(ParameterizedItem *item)
//{

//    DistributionGaussianItem *gausItem = dynamic_cast<DistributionGaussianItem *>(item);
//    Q_ASSERT(gausItem);

//    DistributionGaussian *gaus = dynamic_cast<DistributionGaussian *>(gausItem->createDistribution());
//    Q_ASSERT(gaus);

//    qDebug() << "TestView::plotItem(ParameterizedItem *item) ->" << gausItem->modelType();
//    qDebug() << gausItem->getRegisteredProperty(DistributionItem::P_NUMBER_OF_SAMPLES).toInt()
//             << gausItem->getRegisteredProperty(DistributionItem::P_SIGMA_FACTOR).toDouble()
//             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_MEAN).toDouble()
//             << gausItem->getRegisteredProperty(DistributionGaussianItem::P_STD_DEV).toDouble()
//              << gaus->getMean()
//              << gaus->getStdDev();
//}



void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";
    // if property_name == BeamDistributionItem::P_DISTRIBUTION
    // property_name => BeamDistributionItem::P_DISTRIBUTION

    if(property_name == BeamDistributionItem::P_DISTRIBUTION) {
        DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
        m_plotwidget->setItem(distrItem);
    }

//    std::cout << distrItem->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() << std::endl;
//*/    qDebug() << "TestView::onSubItemChanged() ->" << property_name << distrItem->modelType();*/
//        std::cout << property_name.toStdString() << std::endl;
}
