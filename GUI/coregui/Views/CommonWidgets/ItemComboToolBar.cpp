// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboToolBar.cpp
//! @brief     Implements class ItemComboToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemComboToolBar.h"
#include <QComboBox>
#include <QAction>

ItemComboToolBar::ItemComboToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_comboBox(new QComboBox)
    , m_comboBoxAction(0)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_comboBox->setFixedWidth(125);

    connect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SIGNAL(comboChanged(QString)));

    m_comboBoxAction = addWidget(m_comboBox);
}

void ItemComboToolBar::addPresentationType(const QString &name)
{
    m_comboBox->addItem(name);
}

QString ItemComboToolBar::currentPresentation() const
{
    return m_comboBox->currentText();
}

//! Adds external actions to tool bar (previous actions will be removed).

void ItemComboToolBar::setActionList(const QList<QAction *> &actionList)
{
    foreach(QAction *action, actions()) {
        removeAction(action);
    }

    foreach(QAction *action, actionList) {
        addAction(action);
        addStyledSeparator();
    }

    addStyledExpand();
//    Q_ASSERT(m_comboBox);
    addAction(m_comboBoxAction);
}
