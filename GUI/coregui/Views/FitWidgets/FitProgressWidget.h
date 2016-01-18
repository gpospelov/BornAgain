// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPROGRESSWIDGET_H
#define FITPROGRESSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QLabel;

class BA_CORE_API_ FitProgressWidget : public QWidget
{
    Q_OBJECT

public:

    FitProgressWidget(QWidget *parent = 0);

public slots:

    void updateStatus(const QString &text);

private:

    QLabel *m_status;

};





#endif
