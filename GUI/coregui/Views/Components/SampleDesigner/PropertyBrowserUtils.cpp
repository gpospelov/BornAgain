#include "PropertyBrowserUtils.h"
#include "MaterialEditor.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>
#include <QPixmap>
#include <iostream>
#include <QDebug>


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


GroupPropertyEdit::GroupPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    m_box = new QComboBox(this);

    connect(m_box, SIGNAL(currentTextChanged(QString)),
            this, SLOT(textChanged(QString)));
}

void GroupPropertyEdit::setGroupProperty(
        const GroupProperty &groupProperty)
{
    if(!m_box->count()) m_box->insertItems(0, groupProperty.getValues());

    m_groupProperty = groupProperty;
    m_box->setCurrentText(m_groupProperty.getValue());
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
    return m_box->sizeHint();
}

QSize GroupPropertyEdit::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

