// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsToolBar.cpp
//! @brief     Implements class ProjectionsToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsToolBar.h"
#include "mainwindow_constants.h"
#include "MaskEditorFlags.h"
#include "ProjectionsEditorActions.h"
#include <QButtonGroup>
#include <QToolButton>
#include <QLabel>

ProjectionsToolBar::ProjectionsToolBar(ProjectionsEditorActions* editorActions, QWidget* parent)
    : QToolBar(parent), m_editorActions(editorActions),
      m_activityButtonGroup(new QButtonGroup(this))
{
    setIconSize(QSize(Constants::toolbar_icon_size, Constants::toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    setup_selection_group();
    setup_shapes_group();

    connect(m_activityButtonGroup, SIGNAL(buttonClicked(int)), this,
            SLOT(onActivityGroupChange(int)));

    m_previousActivity = currentActivity();
}

void ProjectionsToolBar::onChangeActivityRequest(MaskEditorFlags::Activity value)
{
    if (value == MaskEditorFlags::PREVIOUS_MODE) {
        setCurrentActivity(m_previousActivity);
    } else {
        m_previousActivity = currentActivity();
        setCurrentActivity(value);
    }
    emit activityModeChanged(currentActivity());
}

void ProjectionsToolBar::onActivityGroupChange(int)
{
    emit activityModeChanged(currentActivity());
}

void ProjectionsToolBar::setup_selection_group()
{
    QToolButton* panButton = new QToolButton(this);
    panButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_hand.svg"));
    panButton->setToolTip("Pan/zoom mode (space)");
    panButton->setCheckable(true);
    panButton->setChecked(true);
    addWidget(panButton);

    QToolButton* resetViewButton = new QToolButton(this);
    resetViewButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_refresh.svg"));
    resetViewButton->setToolTip("Reset pan/zoom to initial state");
    addWidget(resetViewButton);

    connect(resetViewButton, SIGNAL(clicked()), m_editorActions, SIGNAL(resetViewRequest()));

    add_separator();

    QToolButton* selectionButton = new QToolButton(this);
    selectionButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_arrow.svg"));
    selectionButton->setToolTip("Select/modify mask");
    selectionButton->setCheckable(true);
    addWidget(selectionButton);

    m_activityButtonGroup->addButton(panButton, MaskEditorFlags::PAN_ZOOM_MODE);
    m_activityButtonGroup->addButton(selectionButton, MaskEditorFlags::SELECTION_MODE);
}

void ProjectionsToolBar::setup_shapes_group()
{
    QToolButton* horizontalLineButton = new QToolButton(this);
    horizontalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_horizontalline.svg"));
    horizontalLineButton->setToolTip("Create horizontal line mask");
    horizontalLineButton->setCheckable(true);
    addWidget(horizontalLineButton);

    QToolButton* verticalLineButton = new QToolButton(this);
    verticalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_verticalline.svg"));
    verticalLineButton->setToolTip("Create vertical line mask");
    verticalLineButton->setCheckable(true);
    addWidget(verticalLineButton);

    m_activityButtonGroup->addButton(verticalLineButton, MaskEditorFlags::VERTICAL_LINE_MODE);
    m_activityButtonGroup->addButton(horizontalLineButton, MaskEditorFlags::HORIZONTAL_LINE_MODE);
}

void ProjectionsToolBar::add_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

MaskEditorFlags::Activity ProjectionsToolBar::currentActivity() const
{
    return MaskEditorFlags::EActivityType(m_activityButtonGroup->checkedId());
}

void ProjectionsToolBar::setCurrentActivity(MaskEditorFlags::Activity value)
{
    m_activityButtonGroup->button(value)->setChecked(true);
}
