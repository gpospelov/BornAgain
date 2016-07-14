// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.cpp
//! @brief     Declares class InfoPanelToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QToolButton>
#include "InfoPanelToolBar.h"

namespace {
const int minimum_size = 25;
}

InfoPanelToolBar::InfoPanelToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_expandButton(new QToolButton)
    , m_closeButton(new QToolButton)
    , m_expanded(false)
{
    setMinimumSize(minimum_size, minimum_size);

    m_expandButton->setIcon(QIcon(":/images/darkarrowup.png"));
    m_expandButton->setToolTip("Collapse/expand view");
    connect(m_expandButton, SIGNAL(clicked()), this, SLOT(onExpandButtonClicked()));

    m_closeButton->setIcon(QIcon(":/images/darkclosebutton.png"));
    m_closeButton->setToolTip("Close viewe");
    connect(m_closeButton, SIGNAL(clicked()), this, SIGNAL(closeButtonClicked()));

    addStyledExpand();
    addWidget(m_expandButton);
    addWidget(m_closeButton);

    setStyleSheet("QToolBar {border-bottom: 1px solid gray}");
}

void InfoPanelToolBar::setExpandStatus(bool status)
{
    m_expanded = status;
    if(m_expanded) {
        m_expandButton->setIcon(QIcon(":/images/darkarrowdown.png"));
    } else {
        m_expandButton->setIcon(QIcon(":/images/darkarrowup.png"));
    }
}

void InfoPanelToolBar::onExpandButtonClicked()
{
    m_expanded = !m_expanded;
    setExpandStatus(m_expanded);
    emit expandButtonClicked();
}

