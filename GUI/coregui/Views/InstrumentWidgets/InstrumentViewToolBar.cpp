// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewToolBar.cpp
//! @brief     Implements class InstrumentViewToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentViewToolBar.h"
#include "InstrumentViewActions.h"
#include <QToolButton>

InstrumentViewToolBar::InstrumentViewToolBar(InstrumentViewActions* actions, QWidget* parent)
    : StyledToolBar(parent)
    , m_addInstrumentButton(new QToolButton)
    , m_removeInstrumentButton(new QToolButton)
    , m_cloneInstrumentButton(new QToolButton)
{
    m_addInstrumentButton->setText("Add");
    m_addInstrumentButton->setIcon(QIcon(":/images/toolbar16light_newitem.svg"));
    m_addInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_addInstrumentButton->setToolTip("Add new instrument");
    addWidget(m_addInstrumentButton);

    m_removeInstrumentButton->setText("Remove");
    m_removeInstrumentButton->setIcon(QIcon(":/images/toolbar16light_recycle.svg"));
    m_removeInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_removeInstrumentButton->setToolTip("Remove currently selected instrument");
    addWidget(m_removeInstrumentButton);

    m_cloneInstrumentButton->setText("Clone");
    m_cloneInstrumentButton->setIcon(QIcon(":/images/toolbar16light_cloneitem.svg"));
    m_cloneInstrumentButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_cloneInstrumentButton->setToolTip("Clone currently selected instrument");
    addWidget(m_cloneInstrumentButton);

    connect(m_addInstrumentButton, SIGNAL(clicked()), actions, SLOT(onAddInstrument()));
    connect(m_removeInstrumentButton, SIGNAL(clicked()), actions, SLOT(onRemoveInstrument()));
    connect(m_cloneInstrumentButton, SIGNAL(clicked()), actions, SLOT(onCloneInstrument()));
}
