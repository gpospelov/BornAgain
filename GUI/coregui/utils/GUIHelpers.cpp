// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIHelpers.cpp
//! @brief     Implements GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIHelpers.h"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

namespace GUIHelpers {

void information(QWidget *parent, const QString &title, const QString &text, const QString &detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Information);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->exec();
}


void warning(QWidget *parent, const QString &title, const QString &text, const QString &detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Warning);
    messageBox->addButton(QMessageBox::Ok);
    messageBox->exec();
}


bool question(QWidget *parent, const QString &title, const QString &text, const QString &detailedText, const QString &yesText, const QString &noText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    messageBox->setIcon(QMessageBox::Question);
    QAbstractButton *yesButton = messageBox->addButton(yesText,
            QMessageBox::AcceptRole);
    messageBox->addButton(noText, QMessageBox::RejectRole);
    messageBox->setDefaultButton(
            qobject_cast<QPushButton*>(yesButton));
    messageBox->exec();
    return messageBox->clickedButton() == yesButton;
}


bool okToDelete(QWidget *parent, const QString &title, const QString &text, const QString &detailedText)
{
    QScopedPointer<QMessageBox> messageBox(new QMessageBox(parent));
    if (parent)
        messageBox->setWindowModality(Qt::WindowModal);
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setWindowTitle(QString("%1 - %2")
            .arg(QApplication::applicationName()).arg(title));
    messageBox->setText(text);
    if (!detailedText.isEmpty())
        messageBox->setInformativeText(detailedText);
    QAbstractButton *deleteButton = messageBox->addButton(
            QObject::tr("&Delete"), QMessageBox::AcceptRole);
    messageBox->addButton(QObject::tr("Do &Not Delete"),
                          QMessageBox::RejectRole);
    messageBox->setDefaultButton(
            qobject_cast<QPushButton*>(deleteButton));
    messageBox->exec();
    return messageBox->clickedButton() == deleteButton;
}

//! returns type of variant
int getVariantType(const QVariant &variant)
{
    int result = variant.type();
    if (result == QVariant::UserType) {
        result = variant.userType();
    }
    return result;
}




} // namespace GUIHelpers
