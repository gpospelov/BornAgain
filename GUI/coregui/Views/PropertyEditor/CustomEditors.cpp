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
#include "ExternalProperty.h"
#include "GroupItemController.h"
#include "ComboProperty.h"
#include "MaterialItemUtils.h"
#include "GUIHelpers.h"
#include <QBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QComboBox>
#include <QColorDialog>
#include <QLineEdit>
#include <QCheckBox>

//! Sets the data from the model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
    initEditor();
}

//! Inits editor widgets from m_data.

void CustomEditor::initEditor() {}

//! Saves the data from the editor and informs external delegates.

void CustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}

// --- MaterialPropertyEditor ---

ExternalPropertyEditor::ExternalPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new LostFocusFilter(this))
    , m_extDialogType(Constants::MaterialEditorExternalType)
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    ExternalProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.text());
    m_pixmapLabel->setPixmap(defProperty.pixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String(" . . . "));
    button->setToolTip("Material selector");
    layout->addWidget(m_pixmapLabel);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &ExternalPropertyEditor::buttonClicked);

    setLayout(layout);
}

void ExternalPropertyEditor::setExternalDialogType(const QString& editorType)
{
    m_extDialogType = editorType;
}

void ExternalPropertyEditor::buttonClicked()
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);
    ExternalProperty property = m_data.value<ExternalProperty>();

    ExternalProperty newProperty;
    if (m_extDialogType == Constants::MaterialEditorExternalType) {
        newProperty = MaterialItemUtils::selectMaterialProperty(property);
    } else if(m_extDialogType == Constants::ColorEditorExternalType) {
        newProperty = MaterialItemUtils::selectColorProperty(property);
    } else {
        throw GUIHelpers::Error("ExternalPropertyEditor::buttonClicked() -> Unexpected dialog");
    }

    removeEventFilter(m_focusFilter);

    if (newProperty.isValid() && newProperty != property)
        setDataIntern(newProperty.variant());
}

void ExternalPropertyEditor::initEditor()
{
    Q_ASSERT(m_data.canConvert<ExternalProperty>());
    ExternalProperty materialProperty = m_data.value<ExternalProperty>();
    m_textLabel->setText(materialProperty.text());
    m_pixmapLabel->setPixmap(materialProperty.pixmap());
}

// --- CustomComboEditor ---

ComboPropertyEditor::ComboPropertyEditor(QWidget* parent)
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

QSize ComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize ComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void ComboPropertyEditor::onIndexChanged(int index)
{
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

void ComboPropertyEditor::initEditor()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, internLabels());
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

QStringList ComboPropertyEditor::internLabels()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.getValues();
}

//! Returns index for QComboBox.

int ComboPropertyEditor::internIndex()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.currentIndex();
}

void ComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &ComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &ComboPropertyEditor::onIndexChanged);
}

// --- ScientificDoublePropertyEditor ---

ScientificDoublePropertyEditor::ScientificDoublePropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_lineEdit(new QLineEdit)
    , m_validator(nullptr)
{
    setAutoFillBackground(true);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_lineEdit);

    m_validator  = new QDoubleValidator(0.0, 1e+100, 1000, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, &QLineEdit::editingFinished,
            this, &ScientificDoublePropertyEditor::onEditingFinished);

    setLayout(layout);
}

void ScientificDoublePropertyEditor::onEditingFinished()
{
    double new_value = m_lineEdit->text().toDouble();

    if(new_value != m_data.toDouble())
        setDataIntern(QVariant::fromValue(new_value));

}

void ScientificDoublePropertyEditor::initEditor()
{
    Q_ASSERT(m_data.type() == QVariant::Double);
    m_lineEdit->setText(QString::number(m_data.toDouble(), 'g'));
}

// --- BoolEditor ---

BoolEditor::BoolEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_checkBox(new QCheckBox)
{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    setLayout(layout);

    connect(m_checkBox, &QCheckBox::toggled, this, &BoolEditor::onCheckBoxChange);
    setFocusProxy(m_checkBox);
    m_checkBox->setText(tr("True"));
}

void BoolEditor::onCheckBoxChange(bool value)
{
    if(value != m_data.toBool())
        setDataIntern(QVariant(value));
}

void BoolEditor::initEditor()
{
    Q_ASSERT(m_data.type() == QVariant::Bool);
    bool value = m_data.toBool();

    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? "True" : "False");
    m_checkBox->blockSignals(false);
}
