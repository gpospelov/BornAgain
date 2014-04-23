#include "PropertyBrowserUtils.h"
#include "MaterialEditor.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>
#include <QPixmap>
#include <iostream>


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
    std::cout << "MaterialPropertyEdit::buttonClicked() " << std::endl;
    MaterialProperty mat = MaterialEditor::selectMaterialProperty();
    if(mat != m_materialProperty && mat.isDefined() ) {
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


FormFactorPropertyEdit::FormFactorPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    m_box = new QComboBox(this);
    m_box->insertItems(0, FormFactorProperty::getFormFactorNames());
    m_box->setCurrentText(m_formFactorProperty.getFormFactorName());

    connect(m_box, SIGNAL(currentTextChanged(QString)),
            this, SLOT(textChanged(QString)));
}

void FormFactorPropertyEdit::setFormFactorProperty(
        const FormFactorProperty &formFactorProperty)
{
    m_formFactorProperty = formFactorProperty;
    m_box->setCurrentText(m_formFactorProperty.getFormFactorName());
}

void FormFactorPropertyEdit::textChanged(QString text)
{
    FormFactorProperty ff(text);
    if (ff != m_formFactorProperty && ff.isDefined()) {
        setFormFactorProperty(ff);
        emit formFactorPropertyChanged(m_formFactorProperty);
    }
}
