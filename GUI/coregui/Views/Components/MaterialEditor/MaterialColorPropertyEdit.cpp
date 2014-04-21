#include "MaterialColorPropertyEdit.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>

MaterialColorPropertyEdit::MaterialColorPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(2);
    layout->setSpacing(0);

    m_textLabel = new QLabel(this);
    //m_textLabel->setText(m_materialProperty.getName());

    m_pixmapLabel = new QLabel(this);
    m_pixmapLabel->setPixmap(m_colorProperty.getPixmap());

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


void MaterialColorPropertyEdit::buttonClicked()
{
    qDebug() << "MaterialColorPropertyEdit::buttonClicked()";
//    MaterialProperty mat = MaterialBrowser::getMaterialProperty();
//    if(mat != m_materialProperty && mat.isDefined() ) {
//        setMaterialProperty(mat);
//        emit materialPropertyChanged(m_materialProperty);
//    }
}


void MaterialColorPropertyEdit::setMaterialColorProperty(
        const MaterialColorProperty &colorProperty)
{
    m_colorProperty = colorProperty;
    //m_textLabel->setText(m_colorProperty.getName());
    m_pixmapLabel->setPixmap(m_colorProperty.getPixmap());
}

