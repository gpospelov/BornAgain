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
{
    setMinimumSize(Constants::styled_toolbar_height, Constants::styled_toolbar_height);

    // Default View
    m_defaultViewButton = new QToolButton;
    m_defaultViewButton->setText("Default View");
    //m_defaultViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_defaultViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_defaultViewButton->setToolTip("Default view of the sample");
    connect(m_defaultViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::defaultViewAction);
    addWidget(m_defaultViewButton);

    addSeparator();

    // Edge View
    m_edgeViewButton = new QToolButton;
    m_edgeViewButton->setText("Edge View");
    //m_edgeViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_edgeViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_edgeViewButton->setToolTip("View the sample from the edge");
    connect(m_edgeViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::edgeViewAction);
    addWidget(m_edgeViewButton);

    addSeparator();

    // Face View
    m_faceViewButton = new QToolButton;
    m_faceViewButton->setText("Face View");
    //m_faceViewButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    m_faceViewButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_faceViewButton->setToolTip("View the sample from the top (face)");
    connect(m_faceViewButton, &QToolButton::clicked, this, &RealSpaceToolBar::faceViewAction);
    addWidget(m_faceViewButton);

    addSeparator();

    // Lock View
    m_lockViewCheckBox = new QCheckBox;
    m_lockViewCheckBox->setText("Lock View");
    m_lockViewCheckBox->setToolTip("Lock/unlock current sample selection");
    m_lockViewCheckBox->setCheckable(true);
    connect(m_lockViewCheckBox, &QCheckBox::clicked,
            this, [&](){emit RealSpaceToolBar::lockViewAction(m_lockViewCheckBox->isChecked());});
    addWidget(m_lockViewCheckBox);

}
