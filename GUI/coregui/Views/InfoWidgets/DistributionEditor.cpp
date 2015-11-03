// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionEditor.cpp
//! @brief     Implements class DistributionEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
#include "DistributionWidget.h"
#include "DistributionEditor.h"
#include "Distributions.h"
#include "qcustomplot.h"
#include "DistributionDialog.h"
#include "GroupBox.h"
#include <QVBoxLayout>
#include <QDebug>

namespace
{
int minimumWidth_of_AwesomePropertyEditor = 250;
}

DistributionEditor::DistributionEditor(QWidget *parent)
    : QWidget(parent), m_item(0), m_plotwidget(0), m_box(new QGroupBox)

{
    m_plotwidget = new DistributionWidget(this);
    m_propertyEditor
        = new AwesomePropertyEditor(this, AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE);

    QVBoxLayout *boxLayout = new QVBoxLayout;
    m_propertyEditor->setMaximumWidth(minimumWidth_of_AwesomePropertyEditor);
    boxLayout->addWidget(m_propertyEditor);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    m_box->setLayout(boxLayout);

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_box);
    verticalLayout->addStretch(1);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_plotwidget, 1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(verticalLayout);

    setLayout(mainLayout);
}

void DistributionEditor::setItem(ParameterizedItem *item)
{
    m_propertyEditor->clearEditor();
    m_propertyEditor->addItemProperties(item, QString(), AwesomePropertyEditor::INSERT_AFTER);

    if (m_item == item)
        return;

    if (m_item) {
        disconnect(m_item, SIGNAL(subItemChanged(QString)), this, SLOT(onSubItemChanged(QString)));
    }
    m_item = item;

    if (!m_item)
        return;

    connect(m_item, SIGNAL(subItemChanged(QString)), this, SLOT(onSubItemChanged(QString)));

    DistributionItem *distrItem = dynamic_cast<DistributionItem *>(
        m_item->getSubItems()[BeamWavelengthItem::P_DISTRIBUTION]);
    Q_ASSERT(distrItem);
    m_plotwidget->setItem(distrItem);
}

void DistributionEditor::onSubItemChanged(const QString &property_name)
{
    if (property_name == BeamDistributionItem::P_DISTRIBUTION) {
        DistributionItem *distrItem
            = dynamic_cast<DistributionItem *>(m_item->getSubItems()[property_name]);
        Q_ASSERT(distrItem);
        m_plotwidget->setItem(distrItem);
    }
}

void DistributionEditor::setNameOfEditor(QString name)
{
    m_box->setTitle(name);
    m_plotwidget->setXAxisName(name);
}

