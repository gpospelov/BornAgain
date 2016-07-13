// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/aboutapplicationdialog.h
//! @brief     Declares class AboutApplicationDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ABOUTAPPLICATIONDIALOG_H
#define ABOUTAPPLICATIONDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <QString>


class QLabel;
class QPushButton;
class QStatusBar;
class QPalette;


//! new project dialog window
class BA_CORE_API_ AboutApplicationDialog : public QDialog
{
    Q_OBJECT
public:
    AboutApplicationDialog(QWidget *parent = 0);


private:
    QPushButton *m_closeButton;
};


#endif // ABOUTAPPLICATIONDIALOG_H
