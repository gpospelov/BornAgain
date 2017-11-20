// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.h
//! @brief     Implements CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "CustomEditors.h"
#include "CustomEventFilters.h"
#include "MaterialProperty.h"
#include "MaterialSvc.h"
#include "GroupProperty.h"
#include <QBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QComboBox>

//! Sets the data from the model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
}

//! Saves the data from editor and inform external delegates.

void CustomEditor::setDataIntern(const QVariant& data)
{
    setData(data);
    dataChanged(m_data);
}

// --- MaterialPropertyEditor ---

MaterialPropertyEditor::MaterialPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new LostFocusFilter(this))
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);

    MaterialProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.getName());
    m_pixmapLabel->setPixmap(defProperty.getPixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->addWidget(m_pixmapLabel, Qt::AlignLeft);
    layout->addWidget(m_textLabel, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &MaterialPropertyEditor::buttonClicked);

    setLayout(layout);
}

void MaterialPropertyEditor::setData(const QVariant& data)
{
    Q_ASSERT(data.canConvert<MaterialProperty>());
    CustomEditor::setData(data);

    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    m_textLabel->setText(materialProperty.getName());
    m_pixmapLabel->setPixmap(materialProperty.getPixmap());
}

void MaterialPropertyEditor::buttonClicked()
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);
    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    MaterialProperty mat = MaterialSvc::selectMaterialProperty(materialProperty);
    removeEventFilter(m_focusFilter);

    if(mat.isDefined() )
        setDataIntern(mat.getVariant());
}

// --- GroupPropertyEditor ---

GroupPropertyEditor::GroupPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_box(new QComboBox)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);

    setLayout(layout);
    setConnected(true);
}

QSize GroupPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize GroupPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void GroupPropertyEditor::setData(const QVariant& data)
{
    Q_ASSERT(data.canConvert<GroupProperty_t>());
    CustomEditor::setData(data);

    setConnected(false);

    GroupProperty_t groupProperty = m_data.value<GroupProperty_t>();
    m_box->clear();
    m_box->insertItems(0, groupProperty->itemLabels());
    m_box->setCurrentIndex(groupProperty->currentIndex());

    setConnected(true);
}

void GroupPropertyEditor::onIndexChanged(int index)
{
    GroupProperty_t groupProperty = m_data.value<GroupProperty_t>();

    if (groupProperty->currentIndex() != index) {
        groupProperty->setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<GroupProperty_t>(groupProperty));
    }

}

void GroupPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &GroupPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &GroupPropertyEditor::onIndexChanged);
}
