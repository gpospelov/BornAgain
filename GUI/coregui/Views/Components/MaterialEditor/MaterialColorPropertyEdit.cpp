#include "MaterialColorPropertyEdit.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDebug>
#include <QRgb>
#include <QColorDialog>

MaterialColorPropertyEdit::MaterialColorPropertyEdit(QWidget *parent)
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
//    layout->insertSpacing(1,100);

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
//        emit materialColorPropertyChanged(m_materialProperty);
//    }

    bool ok = false;
    QRgb oldRgba = m_colorProperty.getColor().rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
    if (ok && newRgba != oldRgba) {
        m_colorProperty.setColor(QColor::fromRgba(newRgba));
        emit materialColorPropertyChanged(m_colorProperty);
    }

}


void MaterialColorPropertyEdit::setMaterialColorProperty(
        const MaterialColorProperty &colorProperty)
{
    m_colorProperty = colorProperty;
    m_textLabel->setText(colorValueText(m_colorProperty.getColor()));
    m_pixmapLabel->setPixmap(m_colorProperty.getPixmap());
}



QString MaterialColorPropertyEdit::colorValueText(const QColor &c)
{
    return QString("[%1, %2, %3] (%4)")
           .arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}


