// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/tooltipdatabase.cpp
//! @brief     Implements class ToolTipDataBase
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef UPDATENOTIFIER_H
#define UPDATENOTIFIER_H

#include "WinDllMacros.h"
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


#endif
