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
    MaterialProperty mat = MaterialEditor::selectMaterialProperty();
    //if(mat != m_materialProperty && mat.isDefined() ) {
    if(mat.isDefined() ) {
        setMaterialProperty(mat);
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
// GroupPropertyEdit
// -----------------------------------------------------------------------------

GroupPropertyEdit::GroupPropertyEdit(QWidget *parent)
    : QWidget(parent)
    , m_box(0)
    , m_label(0)
{
//    m_box = new QComboBox(this);

//    connect(m_box, SIGNAL(currentTextChanged(QString)),
//            this, SLOT(textChanged(QString)));
}

//void GroupPropertyEdit::setGroupProperty(
//        const GroupProperty &groupProperty)
//{
//    if(!m_box->count()) m_box->insertItems(0, groupProperty.getValues());

//    m_groupProperty = groupProperty;
//    m_box->setCurrentText(m_groupProperty.getValue());
//}


void GroupPropertyEdit::setGroupProperty(
        const GroupProperty &groupProperty)
{
    if(groupProperty.getGroupType() == GroupProperty::ComboGroup) {
        if(!m_box) {
            m_box = new QComboBox(this);

            connect(m_box, SIGNAL(currentTextChanged(QString)),
                    this, SLOT(textChanged(QString)));

        }
        if(!m_box->count()) m_box->insertItems(0, groupProperty.getValues());

        m_groupProperty = groupProperty;
        m_box->setCurrentText(m_groupProperty.getValue());
    }
    else if(groupProperty.getGroupType() == GroupProperty::FixedGroup) {
        if(!m_label) {
            m_label = new QLabel(this);
        }
        m_groupProperty = groupProperty;
        m_label->setText(m_groupProperty.getValue());

    }
    else {
        throw GUIHelpers::Error("GroupPropertyEdit::setGroupProperty() -> Error. Unknown group type.");

    }
}


void GroupPropertyEdit::textChanged(QString text)
{
    GroupProperty ff(m_groupProperty.getGroupName(), text);
    if (ff != m_groupProperty && ff.isDefined()) {
        setGroupProperty(ff);
        emit groupPropertyChanged(m_groupProperty);
    }
}

QSize GroupPropertyEdit::sizeHint() const
{
    if(m_box) {
        return m_box->sizeHint();
    }
    if(m_label) {
        return m_label->sizeHint();
    }
    return QSize(10,10);
}

QSize GroupPropertyEdit::minimumSizeHint() const
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
// ColorPropertyEdit
// -----------------------------------------------------------------------------


ScientificDoublePropertyEdit::ScientificDoublePropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    m_lineEdit = new QLineEdit(this);

    m_validator  = new QDoubleValidator(0.0, 1e+100, 2, this);
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
