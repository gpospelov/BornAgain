// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h
//! @brief     Defines MultiComboPropertyEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiComboPropertyEditor.h"
#include "ComboProperty.h"
#include "CustomEventFilters.h"
#include <QComboBox>
#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QListView>
#include <QMouseEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>

QCheckListStyledItemDelegate::QCheckListStyledItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void QCheckListStyledItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    QStyleOptionViewItem& styleOption = const_cast<QStyleOptionViewItem&>(option);
    styleOption.showDecorationSelected = false;
    QStyledItemDelegate::paint(painter, styleOption, index);
}

// ----------------------------------------------------------------------------
// https://stackoverflow.com/questions/8422760/combobox-of-checkboxes
// https://stackoverflow.com/questions/21186779/catch-mouse-button-pressed-signal-from-qcombobox-popup-menu
// https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720
// ----------------------------------------------------------------------------

MultiComboPropertyEditor::MultiComboPropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox), m_wheel_event_filter(new WheelEventEater(this)),
      m_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheel_event_filter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), &QLineEdit::selectionChanged,
            m_box->lineEdit(), &QLineEdit::deselect);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);
    setConnected(true);
}

QSize MultiComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize MultiComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void MultiComboPropertyEditor::onIndexChanged(int index)
{
    qDebug() << "   onIndexChanged" << index;

    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

//! Propagate check state from the model to ComboProperty.

void MultiComboPropertyEditor::onModelDataChanged(const QModelIndex& topLeft,
                                                  const QModelIndex& /*bottomRight*/,
                                                  const QVector<int>& roles)
{
    if (!roles.contains(Qt::CheckStateRole))
        return;

    auto item = m_model->itemFromIndex(topLeft);
    if (!item)
        return;

    qDebug() << "onModelDataChnaged" << topLeft << roles;
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (item->checkState() == Qt::Unchecked) {
        comboProperty.setSelected(topLeft.row(), false);
        qDebug() << "Unchecked!";
    } else if (item->checkState() == Qt::Checked) {
        qDebug() << "checked!";
        comboProperty.setSelected(topLeft.row(), true);
    }

    updateBoxLabel();
    setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void MultiComboPropertyEditor::onClickedList(const QModelIndex& index)
{
    qDebug() << "   onPressedList" << index;
    if (auto item = m_model->itemFromIndex(index)) {
        auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

//! Handles mouse clicks on QComboBox elements.

bool MultiComboPropertyEditor::eventFilter(QObject* obj, QEvent* event)
{
    // Handles mouse clicks on QListView when it is expanded from QComboBox
    // 1) Prevents list from closing while selecting items.
    // 2) Correctly calculates underlying model index when mouse is over check box style element.
    if (obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease) {
        const auto mouseEvent = static_cast<const QMouseEvent*>(event);
        auto index = m_box->view()->indexAt(mouseEvent->pos());
        onClickedList(index);
        return true;

        // Expands box when clicking on None/Multiple label
    } else if (obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease) {
        m_box->showPopup();
        return true;

    } else {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void MultiComboPropertyEditor::initEditor()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty property = m_data.value<ComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.getValues();
    auto selectedIndices = property.selectedIndices();
    auto currentIndex = property.currentIndex();

    qDebug() << "--------------------------------";
    qDebug() << "xxx" << selectedIndices << currentIndex;

    for (int i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(labels[i]);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        if (selectedIndices.contains(i))
            item->setData(Qt::Checked, Qt::CheckStateRole);
        else
            item->setData(Qt::Unchecked, Qt::CheckStateRole);

        m_model->invisibleRootItem()->appendRow(item);
    }

    setConnected(true);
    updateBoxLabel();
}

void MultiComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &MultiComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
        connect(m_model, &QStandardItemModel::dataChanged, this,
                &MultiComboPropertyEditor::onModelDataChanged);
    } else {
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &MultiComboPropertyEditor::onIndexChanged);
        disconnect(m_model, &QStandardItemModel::dataChanged, this,
                   &MultiComboPropertyEditor::onModelDataChanged);
    }
}

//! Update text on QComboBox depending from amount of selected items.
//! "None" if no items selected
//! "Item text" if one item is selected
//! "2 linked" if more than one item selected

void MultiComboPropertyEditor::updateBoxLabel()
{
    QString text("None");
    int nselected(0);
    for (int row = 0; row < m_model->rowCount(); row++) {
        if (m_model->item(row)->checkState() == Qt::Checked) {
            nselected++;
            if (nselected == 1)
                text = m_model->item(row)->text();
        }
    }
    if (nselected > 1)
        text = QString("%1 linked").arg(nselected);
    m_box->setCurrentText(text);
}
