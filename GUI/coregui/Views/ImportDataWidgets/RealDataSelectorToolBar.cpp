// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.cpp
//! @brief     Implements class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataSelectorToolBar.h"
#include "RealDataSelectorActions.h"
#include <QToolButton>

RealDataSelectorToolBar::RealDataSelectorToolBar(RealDataSelectorActions* actions, QWidget* parent)
    : StyledToolBar(parent)
    , m_importBornAgainDataButton(new QToolButton)
    , m_importAsciiDataButton(new QToolButton)
    , m_removeDataButton(new QToolButton)
{
    setMinimumSize(minimumHeight(), minimumHeight());

    m_importBornAgainDataButton->setText(QStringLiteral("Import data"));
    m_importBornAgainDataButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importBornAgainDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_importBornAgainDataButton->setToolTip("Import Bornagain data formats.");
    addWidget(m_importBornAgainDataButton);

    m_importAsciiDataButton->setText(QStringLiteral("Import Assistant"));
    m_importAsciiDataButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_importAsciiDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_importAsciiDataButton->setToolTip("Import column ascii files.");
    addWidget(m_importAsciiDataButton);

    m_removeDataButton->setText("Remove");
    m_removeDataButton->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeDataButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeDataButton->setToolTip("Remove selected data.");
    addWidget(m_removeDataButton);

    connect(m_importBornAgainDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onImportBornAgainDataAction);
    connect(m_importAsciiDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onImportAsciiDataAction);
    connect(m_removeDataButton, &QToolButton::clicked, actions,
            &RealDataSelectorActions::onRemoveDataAction);
}
