// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobMessagePanel.h
//! @brief     Declares class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBMESSAGEPANEL_H
#define JOBMESSAGEPANEL_H

#include <QColor>
#include "InfoPanel.h"

class QTextEdit;

//! The JobMessagePanel class shows log messages from FitActivityPanel at the
//! bottom part of JobView.

class BA_CORE_API_ JobMessagePanel : public InfoPanel
{
    Q_OBJECT
public:
    JobMessagePanel(QWidget *parent = 0);

public slots:
    void onClearLog();
    void onMessage(const QString &message, const QColor &color = QColor(Qt::black));

private:
    QTextEdit *m_plainLog;
};

#endif // JOBMESSAGEPANEL_H
