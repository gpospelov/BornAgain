// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/ComboSelectorDialog.cpp
//! @brief     Implements class ComboSelectorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComboSelectorDialog.h"
#include "DesignerHelper.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QComboBox>
#include <QMessageBox>

ComboSelectorDialog::ComboSelectorDialog(QWidget* parent)
    : QDialog(parent)
    , m_topLabel(new QLabel)
    , m_comboSelector(new QComboBox)
    , m_bottomLabel(new QLabel)
{
    QColor bgColor(240,240,240,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    setFixedSize(550, 250);
    setWindowTitle("Please make a selection");
    setWindowFlags( Qt::Dialog );

    auto topLayout = new QHBoxLayout;
    topLayout->addLayout(createLogoLayout());
    topLayout->addLayout(createInfoLayout());

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(createButtonLayout());

    setLayout(mainLayout);
}

void ComboSelectorDialog::addItems(const QStringList& selection, const QString& currentItem)
{
    m_comboSelector->addItems(selection);

    if (selection.contains(currentItem))
        m_comboSelector->setCurrentIndex(selection.indexOf(currentItem));
}

void ComboSelectorDialog::setTextTop(const QString& text)
{
    m_topLabel->setText(text);
}

void ComboSelectorDialog::setTextBottom(const QString& text)
{
    m_bottomLabel->setText(text);
}

QString ComboSelectorDialog::currentText() const
{
    return m_comboSelector->currentText();
}

//! Returns layout with icon for left part of the widget.

QBoxLayout* ComboSelectorDialog::createLogoLayout()
{
    auto result = new QVBoxLayout;

    QIcon icon = qApp->style()->standardIcon(QStyle::SP_MessageBoxQuestion);

    auto label = new QLabel;
    label->setPixmap(icon.pixmap(100));

    result->addWidget(label);
    result->setContentsMargins(5, 5, 0, 5);

    return result;
}

//! Create right layout with text and QComboBox selection.

QBoxLayout* ComboSelectorDialog::createInfoLayout()
{
    auto result = new QVBoxLayout;

    m_topLabel->setWordWrap(true);
    m_bottomLabel->setWordWrap(true);

    result->addWidget(m_topLabel);
    result->addStretch(1);
    result->addWidget(m_comboSelector);
    result->addStretch(1);
    result->addWidget(m_bottomLabel);
    result->addStretch(1);
    result->setContentsMargins(0, 5, 5, 5);

    return result;
}

//! Creates button layout with buttons.

QBoxLayout* ComboSelectorDialog::createButtonLayout()
{
    auto result = new QHBoxLayout;

    auto cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    auto okButton = new QPushButton("Try current selection");
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

    result->addStretch(1);
    result->addWidget(okButton);
    result->addWidget(cancelButton);

    return result;
}
