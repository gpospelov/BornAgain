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

#include <QAction>
#include <QComboBox>
#include "ItemComboToolBar.h"

ItemComboToolBar::ItemComboToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_comboBox(new QComboBox)
    , m_comboBoxAction(0)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_comboBox->setFixedWidth(125);
    m_comboBox->setToolTip("Select type of graphical presentation.");

    m_comboBoxAction = addWidget(m_comboBox);

    setComboConnected(true);
}

void ItemComboToolBar::setPresentation(const QString &name)
{
    setComboConnected(false);
    m_comboBox->setCurrentText(name);
    setComboConnected(true);
}

void ItemComboToolBar::addPresentationType(const QString &name)
{
    setComboConnected(false);
    m_comboBox->addItem(name);
    setComboConnected(true);
}

void ItemComboToolBar::setPresentationList(const QStringList &presentationList)
{
    Q_ASSERT(presentationList.size());

    setComboConnected(false);
    m_comboBox->addItems(presentationList);
    setComboConnected(true);
}

QString ItemComboToolBar::currentPresentation() const
{
    return m_comboBox->currentText();
}

//! Sets external actions to tool bar (previous actions will be removed).

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
    addAction(m_comboBoxAction);
}

void ItemComboToolBar::setComboConnected(bool value)
{
    if(value) {
        connect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
                this, SIGNAL(comboChanged(QString)), Qt::UniqueConnection);
    } else {
        disconnect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
                this, SIGNAL(comboChanged(QString)));
    }
}
