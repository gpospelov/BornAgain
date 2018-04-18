// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceToolBar.cpp
//! @brief     Implements class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceToolBar.h"
#include "mainwindow_constants.h"

#include <QToolButton>
#include <QCheckBox>

RealSpaceToolBar::RealSpaceToolBar(QWidget* parent)
    : StyledToolBar(parent)
    , m_defaultViewButton(new QToolButton)
    , m_sideViewButton(new QToolButton)
    , m_topViewButton(new QToolButton)
    , m_lockViewCheckBox(new QCheckBox)
{
    setMinimumSize(Constants::styled_toolbar_height, Constants::styled_toolbar_height);

    // Default View
    m_defaultViewButton->setText("Default View");
    //m_defaultViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_defaultViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_defaultViewButton->setToolTip("Default view of the sample");
    connect(m_defaultViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::defaultViewAction);
    addWidget(m_defaultViewButton);

    addSeparator();

    // Side View
    m_sideViewButton->setText("Side View");
    //m_sideViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_sideViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_sideViewButton->setToolTip("View the sample from the side");
    connect(m_sideViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::sideViewAction);
    addWidget(m_sideViewButton);

    addSeparator();

    // Top View
    m_topViewButton->setText("Top View");
    //m_topViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_topViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_topViewButton->setToolTip("View the sample from the top");
    connect(m_topViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::topViewAction);
    addWidget(m_topViewButton);

    addSeparator();

    // Lock View
    m_lockViewCheckBox->setText("Lock View");
    m_lockViewCheckBox->setToolTip("Lock/unlock current sample selection");
    m_lockViewCheckBox->setCheckable(true);
    connect(m_lockViewCheckBox, &QCheckBox::clicked,
            this, [&](){emit RealSpaceToolBar::lockViewAction(m_lockViewCheckBox->isChecked());});
    addWidget(m_lockViewCheckBox);

}
