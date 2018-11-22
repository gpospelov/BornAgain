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
#include <QStandardItem>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QListView>


QCheckListStyledItemDelegate::QCheckListStyledItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void QCheckListStyledItemDelegate::paint(QPainter* painter_, const QStyleOptionViewItem& option_,
                                         const QModelIndex& index_) const
{
    QStyleOptionViewItem& refToNonConstOption = const_cast<QStyleOptionViewItem&>(option_);
    refToNonConstOption.showDecorationSelected = false;
    QStyledItemDelegate::paint(painter_, refToNonConstOption, index_);
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

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);

    m_box->installEventFilter(m_wheel_event_filter);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);
    connect(m_box->view(), &QListView::pressed, this, &MultiComboPropertyEditor::onPressedList);

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
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

void MultiComboPropertyEditor::onModelDataChanged(const QModelIndex& topLeft,
                                                  const QModelIndex& bottomRight,
                                                  const QVector<int>& roles)
{
    qDebug() << "onModelDataChnaged" << topLeft << roles;
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    auto item = m_model->itemFromIndex(topLeft);
    if (item->checkState() == Qt::Unchecked) {
        comboProperty.setSelected(topLeft.row(), false);
        qDebug() << "Unchecked!";
    } else if (item->checkState() == Qt::Checked) {
        qDebug() << "checked!";
        comboProperty.setSelected(topLeft.row(), true);
    }

    setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void MultiComboPropertyEditor::onPressedList(const QModelIndex& index)
{
    auto item = m_model->itemFromIndex(index);
    auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
    item->setCheckState(state);
}


void MultiComboPropertyEditor::initEditor()
{
    qDebug() << "MultiComboPropertyEditor::initEditor()";
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty property = m_data.value<ComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.getValues();
    auto selectedIndices = property.selectedIndices();
    auto currentIndex = property.currentIndex();

    qDebug() << "xxx" << selectedIndices << currentIndex;

    for (int i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(labels[i]);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable
                       | Qt::ItemIsSelectable);

        if(selectedIndices.contains(i))
            item->setData(Qt::Checked, Qt::CheckStateRole);
        else
            item->setData(Qt::Unchecked, Qt::CheckStateRole);

        m_model->invisibleRootItem()->appendRow(item);
    }

    m_box->setCurrentIndex(currentIndex);

    setConnected(true);
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
