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

ItemComboToolBar::ItemComboToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_comboBox(new QComboBox)
{
    connect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SIGNAL(comboChanged(QString)));

    addWidget(m_comboBox);
}

void ItemComboToolBar::addPresentationType(const QString &name)
{
    m_comboBox->addItem(name);
}

QString ItemComboToolBar::currentPresentation() const
{
    return m_comboBox->currentText();
}
