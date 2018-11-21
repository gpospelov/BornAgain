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
#include "CustomEventFilters.h"
#include "ComboProperty.h"
#include <QVBoxLayout>
#include <QComboBox>

MultiComboPropertyEditor::MultiComboPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_box(new QComboBox)
    , m_wheel_event_filter(new WheelEventEater(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);

    m_box->installEventFilter(m_wheel_event_filter);

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

void MultiComboPropertyEditor::initEditor()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, internLabels());
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

QStringList MultiComboPropertyEditor::internLabels()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.getValues();
}

//! Returns index for QComboBox.

int MultiComboPropertyEditor::internIndex()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.currentIndex();
}

void MultiComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &MultiComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &MultiComboPropertyEditor::onIndexChanged);
}
