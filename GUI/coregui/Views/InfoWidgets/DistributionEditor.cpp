#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include <iostream>
#include "GroupBox.h"
#include <DistributionDialog.h>

DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_plotwidget(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    BeamWavelengthItem *item = new BeamWavelengthItem;
    m_plotwidget = new DistributionWidget(this);
    m_propertyEditor = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
//    GroupBox *box = new GroupBox;
//    box->setTitle("Wavelength dfgfdgfd gdf");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_plotwidget, 1);
    mainLayout->addWidget(m_propertyEditor);
//    mainLayout->addWidget(box,1);
    setLayout(mainLayout);

//    connect(box, SIGNAL(clicked()),
//                        this, SLOT(infoButton()));
}

void DistributionEditor::setItem(ParameterizedItem *item)
{
//    m_propertyEditor->setItem(item);
    m_propertyEditor->clearEditor();


    m_propertyEditor->addItemProperties(item, item->itemName(), AwesomePropertyEditor::INSERT_AFTER);

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(onSubItemChanged(QString)));
    }
    m_item = item;

    if (!m_item) return;

    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(onSubItemChanged(QString)));

    DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[BeamWavelengthItem::P_DISTRIBUTION]);
    Q_ASSERT(distrItem);
    m_plotwidget->setItem(distrItem);

}

void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    if(property_name == BeamDistributionItem::P_DISTRIBUTION) {
        DistributionItem *distrItem = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
        Q_ASSERT(distrItem);
        m_plotwidget->setItem(distrItem);
    }
}

//void DistributionEditor::infoButton()
//{
//    std::cout << "here" << std::endl;
//    DistributionDialog *dialog= new DistributionDialog;

//}
