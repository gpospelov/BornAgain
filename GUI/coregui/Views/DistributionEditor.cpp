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

//    BeamWavelengthItem *item = new BeamWavelengthItem;
    m_plotwidget = new DistributionWidget(this);
    m_propertyEditor = new AwesomePropertyEditor(this);

//    setItem(item);
    m_mainLayout->addWidget(m_plotwidget, 1);
    m_mainLayout->addWidget(m_propertyEditor);
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

    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(onSubItemChanged(QString)));

}

void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    // if property_name == BeamDistributionItem::P_DISTRIBUTION
    // property_name => BeamDistributionItem::P_DISTRIBUTION

    if(property_name == BeamDistributionItem::P_DISTRIBUTION) {
        DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
        // FIXME check is necessary if distrItem exists, at least an Q_ASSERT
        m_plotwidget->setItem(distrItem);
    }
//    else {
//        DistributionNoneItem *distrItem = dynamic_cast<DistributionNoneItem *>(m_item->getSubItems()[property_name]);
//        m_plotwidget->setItem(distrItem);
//    }


//    std::cout << distrItem->getRegisteredProperty(DistributionItem::P_NAME).toString().toStdString() << std::endl;
//*/    qDebug() << "TestView::onSubItemChanged() ->" << property_name << distrItem->modelType();*/
//        std::cout << property_name.toStdString() << std::endl;
}
