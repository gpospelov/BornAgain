#include "PropertyBrowserUtils.h"

#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QFocusEvent>
#include <QPixmap>

#include <iostream>

MaterialPropertyEdit::MaterialPropertyEdit(QWidget *parent)
    : QWidget(parent)
{
    std::cout << "FileEdit::FileEdit() -> XXX" << std::endl;
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
//    theLineEdit = new QLineEdit(this);
//    theLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    m_label = new QLabel(this);
   // m_label->setPixmap(m_materialProperty.getPixmap());
    m_label->setText(m_materialProperty.getName());


    QToolButton *button = new QToolButton(this);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
//    layout->addWidget(theLineEdit);
    layout->addWidget(m_label);
    layout->addWidget(button);
//    setFocusProxy(theLineEdit);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
//    connect(theLineEdit, SIGNAL(textEdited(const QString &)),
//                this, SIGNAL(filePathChanged(const QString &)));
    connect(button, SIGNAL(clicked()),
                this, SLOT(buttonClicked()));
}

void MaterialPropertyEdit::buttonClicked()
{
    std::cout << "MaterialPropertyEdit::buttonClicked() -> " << std::endl;
    QString filePath = QFileDialog::getOpenFileName(this, tr("Choose a file"), theLineEdit->text(), theFilter);
    if (filePath.isNull())
//        return;
//    theLineEdit->setText(filePath);
    m_label->setText(filePath);
    //emit filePathChanged(filePath);
    emit materialPropertyChanged(m_materialProperty);
}

void MaterialPropertyEdit::focusInEvent(QFocusEvent *e)
{
    std::cout << "MaterialPropertyEdit::focusInEvent() -> " << std::endl;
//    theLineEdit->event(e);
//    if (e->reason() == Qt::TabFocusReason || e->reason() == Qt::BacktabFocusReason) {
//        theLineEdit->selectAll();
//    }
    QWidget::focusInEvent(e);
}

void MaterialPropertyEdit::focusOutEvent(QFocusEvent *e)
{
    std::cout << "MaterialPropertyEdit::focusOutEvent() -> " << std::endl;
//    theLineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void MaterialPropertyEdit::keyPressEvent(QKeyEvent *e)
{
    std::cout << "MaterialPropertyEdit::keyPressEvent() -> " << std::endl;
//    theLineEdit->event(e);
}

void MaterialPropertyEdit::keyReleaseEvent(QKeyEvent *e)
{
    std::cout << "MaterialPropertyEdit::keyReleaseEvent() -> " << std::endl;
//    theLineEdit->event(e);
}
