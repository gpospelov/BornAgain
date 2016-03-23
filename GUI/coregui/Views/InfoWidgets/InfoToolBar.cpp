// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoToolBar.cpp
//! @brief     Implements class InfoToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InfoToolBar.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QStyle>
#include <QDebug>

InfoToolBar::InfoToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_expandButton(new QToolButton)
    , m_closeButton(new QToolButton)
    , m_expanded(false)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setMinimumSize(25, 25);

    m_expandButton->setIcon(QIcon(":/images/darkarrowup.png"));
    m_expandButton->setToolTip("Collapse/expand of Python script viewer");
    connect(m_expandButton, SIGNAL(clicked()), this, SLOT(onExpandButtonClicked()));

    m_closeButton->setIcon(QIcon(":/images/darkclosebutton.png"));
    m_closeButton->setToolTip("Close Python script viewer");
    connect(m_closeButton, SIGNAL(clicked()), this, SIGNAL(closeButtonClicked()));

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    addWidget(m_expandButton);
    addWidget(m_closeButton);

    setStyleSheet("QToolBar {border-bottom: 1px solid gray}");
}

void InfoToolBar::setExpandStatus(bool status)
{
    m_expanded = status;
    if(m_expanded) {
        m_expandButton->setIcon(QIcon(":/images/darkarrowdown.png"));
    } else {
        m_expandButton->setIcon(QIcon(":/images/darkarrowup.png"));
    }
}

void InfoToolBar::onExpandButtonClicked()
{
    m_expanded = !m_expanded;
    setExpandStatus(m_expanded);
    emit expandButtonClicked();
}

