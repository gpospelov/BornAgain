// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifier.cpp
//! @brief     Implements class UpdateNotifier
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <QMessageBox>
#include <QtNetwork>
#include "GUIHelpers.h"
#include "mainwindow_constants.h"
#include "UpdateNotifier.h"

UpdateNotifier::UpdateNotifier(QObject *parent)
    : QObject(parent), m_networkAccessManager(new QNetworkAccessManager(parent))
{
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)), this,
            SLOT(replyFinished(QNetworkReply *)));
}

void UpdateNotifier::checkForUpdates()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_UPDATES)) {
        settings.beginGroup(Constants::S_UPDATES);
        if (settings.value(Constants::S_CHECKFORUPDATES).toBool()) {
            QString address(Constants::S_VERSION_URL);
            QUrl url(address);
            QNetworkRequest networkRequest(url);
            networkRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
            QString text = QString("Mozilla/5.0 (BornAgainGUI-%1)").arg(GUIHelpers::getBornAgainVersionString());
            networkRequest.setRawHeader(QByteArray("User-Agent"), text.toLatin1());
            m_networkAccessManager->get(networkRequest);
        } else
            emit onUpdateNotification(QString(""));
    }
}

void UpdateNotifier::replyFinished(QNetworkReply *reply)
{
    QString replyString;
    if (reply->error() == QNetworkReply::NoError) {
        if (reply->isReadable()) {
            // Reading the first line of ChangeLog
            replyString = QString::fromUtf8(reply->readLine().data());
            int versionIndex = replyString.indexOf("-") + 1;
            int versionIndexEnd = replyString.indexOf(",", versionIndex);
            QString versionString = replyString.mid(versionIndex, versionIndexEnd - versionIndex);
            QString myVersion = GUIHelpers::getBornAgainVersionString();

            // Testwise degrade version
            // QString myVersion = QString("1.3.0");

            int compareResult = versionString.compare(myVersion);
            if (compareResult > 0) {
                QString message("New version is available: <a href=\"");
                message.append(Constants::S_DOWNLOAD_LINK);
                message.append("\">");
                message.append(replyString);
                message.append("</a>");
                emit onUpdateNotification(message);
            }
        }
    };
    reply->deleteLater();
}

void UpdateNotifier::askForUpdates()
{
    QSettings settings;
    if (!settings.childGroups().contains(Constants::S_UPDATES)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Updates");
        msgBox.setText("Should BornAgain check for updates automatically?\n"
                       "This setting can be changed later in the main window Settings menu.");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        settings.beginGroup(Constants::S_UPDATES);
        settings.setValue(Constants::S_CHECKFORUPDATES, ret == QMessageBox::Yes);
        settings.endGroup();
    }
    this->checkForUpdates();
}
