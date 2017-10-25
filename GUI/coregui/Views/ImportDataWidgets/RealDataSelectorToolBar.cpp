// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.cpp
//! @brief     Implements class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataSelectorToolBar.h"
#include "RealDataSelectorActions.h"
#include <QToolButton>

RealDataSelectorToolBar::RealDataSelectorToolBar(RealDataSelectorActions* actions, QWidget* parent)
    : StyledToolBar(parent)
    , m_importDataButton(new QToolButton)
    , m_removeDataButton(new QToolButton)
{
    setMinimumSize(minimumHeight(), minimumHeight());

    m_importDataButton->setText(QStringLiteral("Import"));
    m_importDataButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_importDataButton->setToolTip("Import data");
    addWidget(m_importDataButton);

    m_removeDataButton->setText("Remove");
    m_removeDataButton->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeDataButton->setToolTip("Remove selected data.");
    addWidget(m_removeDataButton);

    connect(m_importDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onImportDataAction);
    connect(m_removeDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onRemoveDataAction);
}
