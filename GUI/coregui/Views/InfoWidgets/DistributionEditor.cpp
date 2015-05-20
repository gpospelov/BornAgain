#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include <iostream>
#include "GroupBox.h"
#include <DistributionDialog.h>

namespace
{
    int minimumWidth_of_AwesomePropertyEditor = 250;
}
DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_plotwidget(0)
    , m_box(new QGroupBox)

{
    m_plotwidget = new DistributionWidget(this);
    m_propertyEditor = new AwesomePropertyEditor(this,AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_plotwidget,1);
    QWidget *widget = new QWidget(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QVBoxLayout *widgetLayout = new QVBoxLayout;
    m_propertyEditor->setMaximumWidth(minimumWidth_of_AwesomePropertyEditor);
    verticalLayout->addWidget(m_propertyEditor);
    m_box->setLayout(verticalLayout);
    widgetLayout->addWidget(m_box);
    widgetLayout->addStretch(1);
    widget->setLayout(widgetLayout);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainLayout->addWidget(widget);
    setLayout(mainLayout);
}

void DistributionEditor::setItem(ParameterizedItem *item)
{
    m_propertyEditor->clearEditor();
    m_propertyEditor->addItemProperties(item, QString(), AwesomePropertyEditor::INSERT_AFTER);

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


void DistributionEditor::setNameOfEditor(QString name)
{
    m_box->setTitle(name);
    m_plotwidget->setXAxisName(name);
}
