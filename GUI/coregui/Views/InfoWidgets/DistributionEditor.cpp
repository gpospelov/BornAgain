// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DistributionEditor.cpp
//! @brief     Implements class DistributionEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "DistributionEditor.h"
#include "BeamWavelengthItem.h"
#include "ComponentBoxEditor.h"
#include "DistributionDialog.h"
#include "DistributionWidget.h"
#include "Distributions.h"
#include "GroupInfoBox.h"
#include "GroupItem.h"
#include "SessionItem.h"
#include "qcustomplot.h"
#include <QVBoxLayout>

namespace
{
int minimum_width = 250;
}

DistributionEditor::DistributionEditor(QWidget* parent)
    : QWidget(parent)
    , m_propertyEditor(new ComponentBoxEditor)
    , m_item(nullptr)
    , m_plotwidget(new DistributionWidget)
    , m_box(new QGroupBox)
{

    auto boxLayout = new QVBoxLayout;
    m_propertyEditor->setMaximumWidth(minimum_width);
    boxLayout->addWidget(m_propertyEditor);
    boxLayout->setContentsMargins(0, 0, 0, 0);
    m_box->setLayout(boxLayout);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_box);
    verticalLayout->addStretch(1);

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_plotwidget, 1);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(verticalLayout);

    setLayout(mainLayout);
}

DistributionEditor::~DistributionEditor()
{
    if (m_item)
        m_item->mapper()->unsubscribe(this);
}

void DistributionEditor::setItem(SessionItem* item)
{
    m_propertyEditor->clearEditor();
    m_propertyEditor->addPropertyItems(item);

    if (m_item == item) {
        return;

    } else {
        if (m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = dynamic_cast<GroupItem*>(item);
        if (!m_item)
            return;

        m_item->mapper()->setOnPropertyChange(
            [this](const QString& name) { onPropertyChanged(name); }, this);

        DistributionItem* distrItem = dynamic_cast<DistributionItem*>(m_item->currentItem());
        Q_ASSERT(distrItem);
        m_plotwidget->setItem(distrItem);
    }
}

void DistributionEditor::onPropertyChanged(const QString& property_name)
{
    if (property_name == GroupItem::T_ITEMS) {
        DistributionItem* distrItem = dynamic_cast<DistributionItem*>(m_item->currentItem());
        Q_ASSERT(distrItem);
        m_plotwidget->setItem(distrItem);
    }
}

void DistributionEditor::setNameOfEditor(QString name)
{
    m_box->setTitle(name);
    m_plotwidget->setXAxisName(name);
}
