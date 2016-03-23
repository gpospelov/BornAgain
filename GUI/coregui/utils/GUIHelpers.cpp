// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIHelpers.cpp
//! @brief     Implements GUIHelpers functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIHelpers.h"
#include "BAVersion.h"
#include <QApplication>
#include <QFile>
#include <QRegExp>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

namespace GUIHelpers {

namespace {
QMap<QString, QString> initializeCharacterMap()
{
    QMap<QString, QString> result;
    result["\\"]= QString("_backslash_");
    result["/"] = QString("_slash_");
    result["\""] = QString("_quote_");
    result["<"] = QString("_lessthan_");
    result[">"] = QString("_greaterthan_");
    result["|"] = QString("_pipe_");
    result["?"] = QString("_questionmark_");
    return result;
}

const QMap<QString, QString> invalidCharacterMap = initializeCharacterMap();

}

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

QString getBornAgainVersionString()
{
    return QString::fromStdString(BornAgain::GetVersionNumber());
}

//! Returns valid file name to be saved on disk. This name is constructed from proposed_name
//! by replacing all special characters with text representation
//! \ backslash
//! / slash
//! " quote
//! < lessthan
//! > greaterthan
//! | pipe
//! ? questionmark
QString getValidFileName(const QString &proposed_name)
{
    QString result = proposed_name;
    for(QMap<QString, QString>::const_iterator it=invalidCharacterMap.begin(); it!=invalidCharacterMap.end(); ++it) {
        result.replace(it.key(), it.value());
    }
    return result;
}


} // namespace GUIHelpers
