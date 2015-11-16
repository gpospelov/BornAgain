// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolPanel.cpp
//! @brief     Implements class MaskEditorToolPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorToolPanel.h"
#include "SessionModel.h"
#include "AwesomePropertyEditor.h"
#include "MaskEditorActivity.h"
#include <QVBoxLayout>
#include <QListView>
#include <QItemSelection>
#include <QModelIndexList>
#include <QButtonGroup>
#include <QToolButton>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

MaskEditorToolPanel::MaskEditorToolPanel(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView)
    , m_propertyEditor(new AwesomePropertyEditor)
    , m_activityButtonGroup(new QButtonGroup(this))
    , m_maskValueGroup(new QButtonGroup(this))
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setObjectName(QLatin1String("MaskEditorToolPanel"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(create_selection_group());
    mainLayout->addWidget(create_drawing_group());
    mainLayout->addWidget(create_mask_value_group());
    mainLayout->addWidget(m_propertyEditor);
    mainLayout->addWidget(m_listView);
    setLayout(mainLayout);

    connect(m_activityButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(onActivityButtonGroupChanged(int)));
    connect(m_maskValueGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(onActivityButtonGroupChanged(int)));

    m_previousActivity = getCurrentActivity();
}

void MaskEditorToolPanel::setModel(SessionModel *model, const QModelIndex &root_index)
{
    m_model = model;
    m_listView->setModel(model);
    m_listView->setRootIndex(root_index);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(m_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

}

QItemSelectionModel *MaskEditorToolPanel::selectionModel()
{
    Q_ASSERT(m_listView);
    return m_listView->selectionModel();
}

//! Handles ZOOM requests from MaskGraphicsView while user press and holds
//! space bar. As soon as space bar is released, activity is returned to previous state.
void MaskEditorToolPanel::onChangeActivityRequest(MaskEditorActivity::Flags value)
{
    qDebug() << "MaskEditorToolPanel::onChangeActivityRequest" << value;
    if(value.testFlag(MaskEditorActivity::PAN_ZOOM_MODE)) {
        m_previousActivity = getCurrentActivity();
        qDebug() << "   XXX m_previousActivity now" << m_previousActivity;
        m_activityButtonGroup->button(MaskEditorActivity::PAN_ZOOM_MODE)->setChecked(true);
    } else {
        qDebug() << "   XXX returning to previous activity" << m_previousActivity << "current is" << getCurrentActivity();
        setCurrentActivity(m_previousActivity);
        qDebug() << "       and now it is" << getCurrentActivity();
    }
    emit activityModeChanged(getCurrentActivity());
}

void MaskEditorToolPanel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
//    qDebug() << "MaskEditorToolPanel::onSessionSelectionChanged:";
//    if(!m_model) return;

//    QModelIndexList indices = selected.indexes();
//    if(indices.size()) {
//        ParameterizedItem *item = m_model->itemForIndex(indices.front());
//        m_propertyEditor->setItem(item);
//    }


}

void MaskEditorToolPanel::onActivityButtonGroupChanged(int value)
{
    Q_UNUSED(value);
    emit activityModeChanged(getCurrentActivity());
}

//! Widget on the top of panel, containing two buttons for selection mode and for pan/zoom mode.
QWidget *MaskEditorToolPanel::create_selection_group()
{
    QWidget *result = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    QPushButton *selectionButton = new QPushButton("Select");
    selectionButton->setCheckable(true);
    selectionButton->setChecked(true);
//    selectionButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_pointer.png"));
    selectionButton->setToolTip("Edit mode.");
    QPushButton *panButton = new QPushButton("Pan/Zoom");
    panButton->setCheckable(true);
//    panButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_hand.png"));
    panButton->setToolTip("Pan mode (space).");

    m_activityButtonGroup->addButton(selectionButton, MaskEditorActivity::SELECTION_MODE);
    m_activityButtonGroup->addButton(panButton, MaskEditorActivity::PAN_ZOOM_MODE);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(selectionButton);
    layout->addWidget(panButton);
    result->setLayout(layout);
    return result;
}

QWidget *MaskEditorToolPanel::create_drawing_group()
{
    QWidget *result = new QWidget;
    QGridLayout *layout = new QGridLayout;

    QPushButton *rectButton = new QPushButton("Rectangle");
    rectButton->setCheckable(true);
    m_activityButtonGroup->addButton(rectButton, MaskEditorActivity::RECTANGLE_MODE);

    QPushButton *polyButton = new QPushButton("Poly");
    polyButton->setCheckable(true);
    m_activityButtonGroup->addButton(polyButton, MaskEditorActivity::POLYGON_MODE);


//    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(rectButton, 0, 0);
    layout->addWidget(polyButton, 0, 1);
    result->setLayout(layout);
    return result;

}

QWidget *MaskEditorToolPanel::create_mask_value_group()
{
    QWidget *result = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    QPushButton *greenButton = new QPushButton("Green");
    greenButton->setCheckable(true);

    QPushButton *redButton = new QPushButton("Red");
    redButton->setCheckable(true);
    redButton->setChecked(true);

    m_maskValueGroup->addButton(greenButton, MaskEditorActivity::MASK_GREEN_ID);
    m_maskValueGroup->addButton(redButton, MaskEditorActivity::MASK_RED_ID);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(greenButton);
    layout->addWidget(redButton);
    result->setLayout(layout);
    return result;

}

MaskEditorActivity::Flags MaskEditorToolPanel::getCurrentActivity() const
{
    MaskEditorActivity::Flags result;
    result |= MaskEditorActivity::EActivityType(m_activityButtonGroup->checkedId());
    result |= MaskEditorActivity::EActivityType(m_maskValueGroup->checkedId());
    qDebug() << "MaskEditorToolPanel::getCurrentActivity():" << result;
    return result;
}

void MaskEditorToolPanel::setCurrentActivity(MaskEditorActivity::Flags value)
{
    if(value.testFlag(MaskEditorActivity::SELECTION_MODE))
        m_activityButtonGroup->button(MaskEditorActivity::SELECTION_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorActivity::PAN_ZOOM_MODE))
        m_activityButtonGroup->button(MaskEditorActivity::PAN_ZOOM_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorActivity::RECTANGLE_MODE))
        m_activityButtonGroup->button(MaskEditorActivity::RECTANGLE_MODE)->setChecked(true);
    if(value.testFlag(MaskEditorActivity::POLYGON_MODE))
        m_activityButtonGroup->button(MaskEditorActivity::POLYGON_MODE)->setChecked(true);

    if(value.testFlag(MaskEditorActivity::MASK_GREEN_ID))
        m_maskValueGroup->button(MaskEditorActivity::MASK_GREEN_ID)->setChecked(true);
    if(value.testFlag(MaskEditorActivity::MASK_RED_ID))
        m_maskValueGroup->button(MaskEditorActivity::MASK_RED_ID)->setChecked(true);

}
