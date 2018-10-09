// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.cpp
//! @brief     Declares class InfoPanelToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InfoPanelToolBar.h"
#include <QHBoxLayout>
#include <QToolButton>

namespace
{
const int minimum_size = 25;
const QString icon_up = ":/images/dark-angle-up.svg";
const QString icon_down = ":/images/dark-angle-down.svg";
const QString icon_close = ":/images/dark-close.svg";
}

InfoPanelToolBar::InfoPanelToolBar(QWidget* parent)
    : StyledToolBar(parent), m_expandButton(new QToolButton), m_closeButton(new QToolButton),
      m_expanded(false)
{
    setMinimumSize(minimum_size, minimum_size);

    m_expandButton->setIcon(QIcon(icon_up));
    m_expandButton->setToolTip("Collapse/expand view");
    connect(m_expandButton, &QToolButton::clicked, this, &InfoPanelToolBar::onExpandButtonClicked);

    m_closeButton->setIcon(QIcon(icon_close));
    m_closeButton->setToolTip("Close viewe");
    connect(m_closeButton, &QToolButton::clicked, this, &InfoPanelToolBar::closeButtonClicked);

    addStyledExpand();
    addWidget(m_expandButton);
    addWidget(m_closeButton);

    setStyleSheet("QToolBar {border-bottom: 1px solid gray}");
}

void InfoPanelToolBar::setExpandStatus(bool status)
{
    m_expanded = status;
    if (m_expanded)
        m_expandButton->setIcon(QIcon(icon_down));
    else
        m_expandButton->setIcon(QIcon(icon_up));
}

void InfoPanelToolBar::onExpandButtonClicked()
{
    m_expanded = !m_expanded;
    setExpandStatus(m_expanded);
    emit expandButtonClicked();
}
