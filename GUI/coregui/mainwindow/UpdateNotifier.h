// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/UpdateNotifier.h
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

#ifndef UPDATENOTIFIER_H
#define UPDATENOTIFIER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class BA_CORE_API_ UpdateNotifier : public QObject
{
    Q_OBJECT
public:
    UpdateNotifier(QObject *parent = 0);
    void checkForUpdates();

public slots:
    void replyFinished(QNetworkReply *reply);
    void askForUpdates();

signals:
    void onUpdateNotification(const QString &text);

private:
    QNetworkAccessManager *m_networkAccessManager;
};


#endif // UPDATENOTIFIER_H
