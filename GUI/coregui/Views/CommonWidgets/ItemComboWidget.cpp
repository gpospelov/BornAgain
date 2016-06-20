// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.cpp
//! @brief     Implements class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemComboWidget.h"
#include <QStackedWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>

ItemComboWidget::ItemComboWidget(QWidget *parent)
    : QWidget(parent)
    , m_selectorCombo(new QComboBox)
    , m_stackedWidget(new QStackedWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    connect(m_selectorCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onWidgetChangeRequest(QString)));
}


void ItemComboWidget::setItem(SessionItem *item)
{
    m_currentItem = item;
}

void ItemComboWidget::add(const QString &presentationType, std::function<QWidget *()> f)
{
    m_widgetFactory.registerItem(presentationType, f);
    m_selectorCombo->addItem(presentationType);
}

QWidget *ItemComboWidget::selectorWidget()
{
    return m_selectorCombo;
}

void ItemComboWidget::onWidgetChangeRequest(const QString &name)
{
    qDebug() << "ItemComboWidget::onWidgetChangeRequest" << name;
}
