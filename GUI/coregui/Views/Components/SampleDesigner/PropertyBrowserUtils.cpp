#include "PropertyBrowserUtils.h"
#include "MaterialEditor.h"
#include "GUIHelpers.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>
#include <QLabel>
#include <QIcon>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QPixmap>
#include <QRgb>
#include <QColorDialog>
#include <QDebug>

// -----------------------------------------------------------------------------
// MaterialPropertyEdit
// -----------------------------------------------------------------------------

MaterialPropertyEdit::MaterialPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(2);
    layout->setSpacing(0);

    m_textLabel = new QLabel(this);
    m_textLabel->setText(m_materialProperty.getName());

    m_pixmapLabel = new QLabel(this);
    m_pixmapLabel->setPixmap(m_materialProperty.getPixmap());

    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,
                                      QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->addWidget(m_pixmapLabel, Qt::AlignLeft);
    layout->addWidget(m_textLabel, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}


void MaterialPropertyEdit::buttonClicked()
{
    qDebug() << "MaterialPropertyEdit::buttonClicked()" << m_materialProperty.getIdentifier();
    MaterialProperty mat = MaterialEditor::selectMaterialProperty();
    qDebug() << "MaterialPropertyEdit::buttonClicked() -> receive" << mat.getIdentifier();
    //if(mat != m_materialProperty && mat.isDefined() ) {
    if(mat.isDefined() ) {
        setMaterialProperty(mat);
        qDebug() << "MaterialPropertyEdit::buttonClicked() -> emitting signal";
        emit materialPropertyChanged(m_materialProperty);
    }
}


void MaterialPropertyEdit::setMaterialProperty(
        const MaterialProperty &materialProperty)
{
    m_materialProperty = materialProperty;
    m_textLabel->setText(m_materialProperty.getName());
    m_pixmapLabel->setPixmap(m_materialProperty.getPixmap());
}


// -----------------------------------------------------------------------------
// FancyGroupPropertyEdit
// -----------------------------------------------------------------------------
FancyGroupPropertyEdit::FancyGroupPropertyEdit(QWidget *parent)
    : QWidget(parent)
    , m_box(0)
    , m_label(0)
    , m_groupProperty(0)
{
}

FancyGroupPropertyEdit::~FancyGroupPropertyEdit()
{
    qDebug() << "FancyGroupPropertyEdit::~FancyGroupPropertyEditor() -> destroyed";

}

void FancyGroupPropertyEdit::setFancyGroupProperty(
        FancyGroupProperty *groupProperty)
{
    qDebug() << "FancyGroupPropertyEdit::setFancyGroupProperty() ->" << groupProperty << groupProperty->getValue()  << groupProperty->getValueLabel();
    if(groupProperty) {
        m_groupProperty = groupProperty;

        if(groupProperty->type() == FancyGroupProperty::FixedGroupType) {
            processFixedGroup();
        }
        else if(groupProperty->type() == FancyGroupProperty::SelectableGroupType) {
            processSelectableGroup();
        }
        else {
            throw GUIHelpers::Error(" FancyGroupPropertyEdit::setFancyGroupProperty() -> Error. Unknown group type");
        }

    }
}


void FancyGroupPropertyEdit::processFixedGroup()
{
    qDebug() << "FancyGroupPropertyEdit::processFixedGroup()" << m_groupProperty->getValueLabel();
    if(!m_label) m_label = new QLabel(this);
    m_label->setText(m_groupProperty->getValueLabel());
}


void FancyGroupPropertyEdit::processSelectableGroup()
{
    if(!m_box) m_box = new QComboBox(this);

    disconnect(m_box, SIGNAL(currentIndexChanged(int)),
            this, SLOT(indexChanged(int)));

    if(!m_box->count()) m_box->insertItems(0, m_groupProperty->getValueLabels());
    m_box->setCurrentIndex(m_groupProperty->index());

    connect(m_box, SIGNAL(currentIndexChanged(int)),
            this, SLOT(indexChanged(int)));

}


void FancyGroupPropertyEdit::indexChanged(int index)
{
    qDebug() << "FancyGroupPropertyEdit::textChanged() -> " << index;
    m_groupProperty->setValue(m_groupProperty->toString(index));
    emit fancyGroupPropertyChanged(m_groupProperty);
}


QSize FancyGroupPropertyEdit::sizeHint() const
{
    if(m_box) {
        return m_box->sizeHint();
    }
    if(m_label) {
        return m_label->sizeHint();
    }
    return QSize(10,10);
}

QSize FancyGroupPropertyEdit::minimumSizeHint() const
{
    if(m_box) {
        return m_box->minimumSizeHint();
    }
    if(m_label) {
        return m_label->minimumSizeHint();
    }
    return QSize(10,10);
}


// -----------------------------------------------------------------------------
// ColorPropertyEdit
// -----------------------------------------------------------------------------

ColorPropertyEdit::ColorPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(2);
    layout->setSpacing(2);

    m_textLabel = new QLabel(this);
    m_textLabel->setText(colorValueText(m_colorProperty.getColor()));

    m_pixmapLabel = new QLabel(this);
    m_pixmapLabel->setPixmap(m_colorProperty.getPixmap());

    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,
                                      QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->insertSpacing(-1,1);
    layout->addWidget(m_pixmapLabel);
    layout->insertSpacing(-1,6);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    layout->addWidget(button);

    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}


void ColorPropertyEdit::buttonClicked()
{
    bool ok = false;
    QRgb oldRgba = m_colorProperty.getColor().rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
    if (ok && newRgba != oldRgba) {
        m_colorProperty.setColor(QColor::fromRgba(newRgba));
        emit colorPropertyChanged(m_colorProperty);
    }

}

void ColorPropertyEdit::setColorProperty(
        const ColorProperty &colorProperty)
{
    m_colorProperty = colorProperty;
    m_textLabel->setText(colorValueText(m_colorProperty.getColor()));
    m_pixmapLabel->setPixmap(m_colorProperty.getPixmap());
}

QString ColorPropertyEdit::colorValueText(const QColor &c)
{
    return QString("[%1, %2, %3] (%4)")
           .arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}


// -----------------------------------------------------------------------------
// ScientificDoublePropertyEdit
// -----------------------------------------------------------------------------


ScientificDoublePropertyEdit::ScientificDoublePropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    m_lineEdit = new QLineEdit(this);

    m_validator  = new QDoubleValidator(0.0, 1e+100, 1000, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, SIGNAL(editingFinished()),
            this, SLOT(onEditingFinished()));
}

void ScientificDoublePropertyEdit::setScientificDoubleProperty(
        const ScientificDoubleProperty &doubleProperty)
{
    m_lineEdit->setText(doubleProperty.getText());
    m_scientificDoubleProperty = doubleProperty;
}

void ScientificDoublePropertyEdit::onEditingFinished()
{
    double new_value = m_lineEdit->text().toDouble();
    if(new_value != m_scientificDoubleProperty.getValue()) {
        ScientificDoubleProperty doubleProperty(new_value);
        setScientificDoubleProperty(doubleProperty);
        emit scientificDoublePropertyChanged(m_scientificDoubleProperty);
    }
}

QSize ScientificDoublePropertyEdit::sizeHint() const
{
    return m_lineEdit->sizeHint();
}

QSize ScientificDoublePropertyEdit::minimumSizeHint() const
{
    return m_lineEdit->minimumSizeHint();
}

// -----------------------------------------------------------------------------
// ComboPropertyEdit
// -----------------------------------------------------------------------------

ComboPropertyEdit::ComboPropertyEdit(QWidget *parent)
    : QWidget(parent)
    , m_comboBox(0)
{
}

void ComboPropertyEdit::setComboProperty(
        const ComboProperty &combo_property)
{
    m_combo_property = combo_property;
    if (!m_comboBox) m_comboBox = new QComboBox(this);

    disconnect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onCurrentIndexChanged(QString)));

    m_comboBox->clear();
    QStringList value_list = m_combo_property.getValues();
    m_comboBox->addItems(value_list);
    m_comboBox->setCurrentText(comboValueText());

    connect(m_comboBox, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(onCurrentIndexChanged(QString)));
}

QString ComboPropertyEdit::comboValueText()
{
    return m_combo_property.getValue();
}

void ComboPropertyEdit::onCurrentIndexChanged(QString current_value)
{
    m_combo_property.setValue(current_value);
    emit comboPropertyChanged(m_combo_property);
}


