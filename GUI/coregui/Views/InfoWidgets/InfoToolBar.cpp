// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoToolBar.cpp
//! @brief     Implements class InfoToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfoToolBar.h"
#include <QHBoxLayout>
#include <QToolButton>

InfoToolBar::InfoToolBar(QWidget *parent)
    : QToolBar(parent)
    , m_expandButton(new QToolButton)
    , m_closeButton(new QToolButton)
{
//    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_expandButton->setIcon(QIcon(":/images/darkarrowdown.png"));
    m_expandButton->setToolTip("Run currently selected job");

    m_closeButton->setIcon(QIcon(":/images/darkclosebutton.png"));
    m_closeButton->setToolTip("Run currently selected job");

//    mainLayout->addStretch();
//    mainLayout->addWidget(m_expandButton);
//    mainLayout->addWidget(m_closeButton);


    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);

    addWidget(m_expandButton);
    addWidget(m_closeButton);


    setStyleSheet("QToolBar {border-bottom: 1px solid gray}");

//    setLayout(mainLayout);
}

