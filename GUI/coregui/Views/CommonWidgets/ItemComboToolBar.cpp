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
#include <QAction>
#include <QStandardItemModel>
#include <QComboBox>

ItemComboToolBar::ItemComboToolBar(QWidget* parent)
    : StyledToolBar(parent), m_comboBox(new QComboBox), m_comboBoxAction(nullptr)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_comboBox->setFixedWidth(125);
    m_comboBox->setToolTip("Select type of graphical presentation.");

    m_comboBoxAction = addWidget(m_comboBox);

    setComboConnected(true);
}

void ItemComboToolBar::setPresentation(const QString& name)
{
    setComboConnected(false);
    m_comboBox->setCurrentText(name);
    setComboConnected(true);
}

void ItemComboToolBar::setPresentationList(const QStringList& presentationList,
                                           const QStringList& activeList)
{
    Q_ASSERT(presentationList.size());

    QString previous = currentPresentation();

    setComboConnected(false);
    m_comboBox->clear();
    m_comboBox->addItems(presentationList);
    if (activeList.contains(previous))
        m_comboBox->setCurrentText(previous);

    if(!activeList.isEmpty())
        makeItemsEnabled(activeList);

    setComboConnected(true);
}

QString ItemComboToolBar::currentPresentation() const
{
    return m_comboBox->currentText();
}

//! Sets external actions to tool bar (previous actions will be removed).

void ItemComboToolBar::setActionList(const QList<QAction*>& actionList)
{
    foreach (QAction* action, actions())
        removeAction(action);

    foreach (QAction* action, actionList) {
        addAction(action);
        addStyledSeparator();
    }

    addStyledExpand();
    addAction(m_comboBoxAction);
}

void ItemComboToolBar::setComboConnected(bool value)
{
    if (value)
        connect(m_comboBox, SIGNAL(currentIndexChanged(QString)), this,
                SIGNAL(comboChanged(QString)), Qt::UniqueConnection);
    else
        disconnect(m_comboBox, SIGNAL(currentIndexChanged(QString)), this,
                   SIGNAL(comboChanged(QString)));
}

//! All items in QComboBox which are not in given list, will be disabled (gray and unselectable).

void ItemComboToolBar::makeItemsEnabled(const QStringList& activePresentations)
{
    const QStandardItemModel* model = dynamic_cast<const QStandardItemModel*>(m_comboBox->model());
    Q_ASSERT(model);

    for(int row=0; row<m_comboBox->count(); ++row) {
        QString text = m_comboBox->itemText(row);
        model->item(row)->setEnabled(activePresentations.contains(text));
    }
}
